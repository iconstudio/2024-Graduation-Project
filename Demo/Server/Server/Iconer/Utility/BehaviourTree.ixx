module;
#include <concurrent_queue.h>

export module Iconer.Utility.BehaviourTree;
import Net.Traits;
import Net.Constraints;
import <variant>;
import <atomic>;

export namespace iconer::util
{
	struct DefaultBehaviour
	{
		template <typename OtherNode>
		static inline constexpr bool Transient = false;
	};

	template <typename Node>
	struct BehaviourTraits
	{
		template <typename OtherNode>
		static inline constexpr bool IsTransient = Node::template Transient<OtherNode>;
	};

	template <typename... NodeTs>
		requires net::argument_available<NodeTs...>
	class [[nodiscard]] BehaviourTree final
	{
	private:
		using data_t = std::variant<NodeTs...>;

	public:
		static_assert(net::default_initializables<NodeTs...>);

		constexpr BehaviourTree() noexcept = default;
		constexpr ~BehaviourTree() noexcept = default;

		template <typename Node>
		constexpr bool TryTranslate() noexcept(std::is_nothrow_assignable_v<data_t, Node>)
		{
			if (std::holds_alternative<Node>(currentState))
			{
				return true;
			}
			else
			{
				data_t state = currentState.load(std::memory_order_acquire);
				if (state.valueless_by_exception())
				{
					state = Node{};
					currentState.store(state, std::memory_order_release);
					return true;
				}
				else
				{
					constexpr auto visitor = [&state]<typename V>(V&& arg) noexcept -> bool {
						if constexpr (BehaviourTraits<std::decay_t<V>>::template IsTransient<Node>)
						{
							return true;
						}
						else
						{
							return false;
						}
					};

					const bool result = std::visit(visitor, state);
					currentState.store(state, std::memory_order_release);
					return result;
				}
			}
		}

		template <typename Fn>
		constexpr decltype(auto) Visit(Fn&& fn) noexcept(std::visit(std::forward<Fn>(fn), currentState))
		{
			if constexpr (net::same_as<decltype(std::visit(std::forward<Fn>(fn), currentState)), void>)
			{
				data_t state = currentState.load(std::memory_order_acquire);
				std::visit(std::forward<Fn>(fn), std::move(state));
				currentState.store(state, std::memory_order_release);
			}
			else
			{
				data_t state = currentState.load(std::memory_order_acquire);
				auto&& result = std::visit(std::forward<Fn>(fn), std::move(state));
				currentState.store(state, std::memory_order_release);

				return result;
			}
		}

		template <typename Fn>
		constexpr decltype(auto) Visit(Fn&& fn) const noexcept(std::visit(std::forward<Fn>(fn), currentState))
		{
			if constexpr (net::same_as<decltype(std::visit(std::forward<Fn>(fn), currentState)), void>)
			{
				std::visit(std::forward<Fn>(fn), currentState.load(std::memory_order_acq_rel));
			}
			else
			{
				return std::visit(std::forward<Fn>(fn), currentState.load(std::memory_order_acq_rel));
			}
		}

	private:
		std::atomic<data_t> currentState;
	};
}
