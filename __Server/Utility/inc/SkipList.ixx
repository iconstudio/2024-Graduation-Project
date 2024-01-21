export module Net.Collection.SkipList;
import Iconer.Constraints;
import <atomic>;
import <mutex>;

export namespace net::collections
{
	template<typename T>
	class SkipList;

	template<notvoids T>
	class SkipList<T>
	{
	private:
		static constexpr ptrdiff_t MAX_LEVEL = 100;

		class NODE_SK
		{
		public:
			constexpr NODE_SK() noexcept : NODE_SK(-1, 0)
			{}

			constexpr NODE_SK(const T& v, const ptrdiff_t& top) noexcept
				: value(v), top_level(top)
				, nexts()
				, isRemoved(false), fullyLinked(false)
			{
				for (auto i = 0; i <= MAX_LEVEL; ++i)
				{
					nexts[i] = nullptr;
				}
			}

			constexpr NODE_SK(T&& v, const ptrdiff_t& top) noexcept
				: value(std::move(v)), top_level(top)
				, nexts()
				, isRemoved(false), fullyLinked(false)
			{
				for (auto i = 0; i <= MAX_LEVEL; ++i)
				{
					nexts[i] = nullptr;
				}
			}

			void lock()
			{
				myMutex.lock();
			}

			void unlock() noexcept
			{
				myMutex.unlock();
			}

			T value;
			ptrdiff_t top_level;

			std::recursive_mutex myMutex;
			NODE_SK* volatile nexts[MAX_LEVEL + 1];

			volatile bool isRemoved;
			volatile bool fullyLinked;
		};

	public:
		SkipList() noexcept
			: head()
		{
			head.value = 0x80000000;
			head.value = 0x7FFFFFFF;
			tail.top_level = head.top_level = MAX_LEVEL;

			for (NODE_SK* volatile& node : head.nexts)
			{
				node = std::addressof(tail);
			}
		}

		constexpr ptrdiff_t Find(const T& x, NODE_SK* pred[], NODE_SK* curr[])
		{
			ptrdiff_t found_level = -1;

			pred[MAX_LEVEL] = &head;

			for (auto i = MAX_LEVEL; i >= 0; --i)
			{
				curr[i] = pred[i]->nexts[i];

				// ��� ����
				while (curr[i]->value < x)
				{
					pred[i] = curr[i];
					curr[i] = curr[i]->nexts[i];
				}

				if (-1 == found_level && curr[i]->value == x)
				{
					found_level = i;
				}

				if (i == 0) break;
				pred[i - 1] = pred[i];
			}

			return found_level;
		}

		bool ADD(const T& x)
		{
			// ��� ������ ���� ������
			NODE_SK* pred[MAX_LEVEL + 1];
			NODE_SK* curr[MAX_LEVEL + 1];

			//std::unique_lock<std::recursive_mutex> guard{ myLocker };

			while (true)
			{
				const ptrdiff_t found_level = Find(x, pred, curr);
				if (-1 != found_level)
				{
					// ������ ���� Add�� �����ϹǷ� �ٽ� ����
					if (curr[found_level]->isRemoved) continue;

					// ���� ����� �� ���� ���
					while (!curr[found_level]->fullyLinked);
					return false;
				}

				const ptrdiff_t valid_level = 0;
				for (ptrdiff_t i = 0; i < MAX_LEVEL; ++i)
				{
					if ((rand() % 2) == 0) break;
					valid_level++;
				}

				// 
				bool valid = false;

				// �ʿ���� ����� ���� ���� ��� �ϳ��� ��׸鼭 ����
				ptrdiff_t last_top_locked_level = 0;

				// ��� ��带 ��װ� ���Ἲ �˻�
				for (ptrdiff_t i = 0; i <= valid_level; i++)
				{
					pred[i]->lock();
					last_top_locked_level = i;

					valid = !pred[i]->isRemoved
						&& !curr[i]->isRemoved
						&& pred[i]->nexts[i] == curr[i];

					if (!valid)
					{
						break;
					}
				}
				if (!valid)
				{
					// recursive_lock�� ��� Ƚ����ŭ �ٽ� ��������� �Ѵ�.
					for (ptrdiff_t k = 0; k < last_top_locked_level; k++)
					{
						pred[k]->unlock();
					}

					continue;
				}

				// ��� ���� �κ�
				auto newbie = new NODE_SK{ x, valid_level };
				for (ptrdiff_t i = 0; i <= valid_level; i++)
				{
					newbie->nexts[i] = curr[i];
				}
				for (ptrdiff_t i = 0; i <= valid_level; i++)
				{
					pred[i]->nexts[i] = newbie;
				}

				for (ptrdiff_t k = 0; k < last_top_locked_level; k++)
				{
					pred[k]->unlock();
				}

				return true;
			}
		}

		bool REMOVE(const T& x)
		{
			// ��� ������ ���� ������
			NODE_SK* pred[MAX_LEVEL + 1]{};
			NODE_SK* curr[MAX_LEVEL + 1]{};

			//std::unique_lock<std::recursive_mutex> guard{ myLocker };
			Find(x, pred, curr);

			if (curr[0]->value != x)
			{
				return false;
			}
			else
			{
				ptrdiff_t max_level = curr[0]->top_level;

				for (ptrdiff_t i = 0; i <= max_level; i++)
				{
					pred[i]->nexts[i] = curr[i]->nexts[i];
				}

				// curr[0~i]�� ����
				auto& target = curr[0];


				return true;
			}

			return false;
		}

		bool CONTAINS(const T& value) const
		{
			auto curr = &head;

			while (curr->value < value)
			{
				curr = curr->nexts[0];
			}

			return curr->value == value;
		}

		void PRINT() const
		{
			NODE_SK* ptr = head.nexts[0];

			for (int i = 0; i < 20; ++i)
			{
				if (ptr == &tail) break;

				//std::print("{}, ", ptr->value);

				ptr = ptr->nexts[0];
			}

			//std::println("");
		}

		void CLEAR()
		{
			auto* ptr = head.nexts[0];
			while (ptr != &tail)
			{
				auto* handle = ptr;
				ptr = ptr->nexts[0];
				delete ptr;
			}
			for (auto& node : head.nexts)
			{
				node = &tail;
			}
		}

		NODE_SK head, tail;
		std::recursive_mutex myLocker;
	};
}
