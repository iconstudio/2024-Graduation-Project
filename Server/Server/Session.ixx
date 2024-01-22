export module Iconer.Application.Session;
import Iconer.Utility.Constraints;
import Iconer.Utility.Handler;

export namespace iconer::app
{
	class [[nodiscard]] Session : public iconer::util::Handler<int32_t>
	{
	public:
		virtual constexpr ~Session() noexcept = default;

		/// <summary>
		/// Excute once at first
		/// </summary>
		/// <returns></returns>
		virtual bool OnAwake() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnDestroy() = 0;

		constexpr Session(Session&&) noexcept = default;
		constexpr Session& operator=(Session&&) noexcept = default;

	protected:
		constexpr Session() noexcept = default;

	private:
		Session(const Session&) = delete;
		void operator=(const Session&) = delete;
	};

	template<typename S>
	class SessionFactory
	{
	public:
		template<typename... Args>
		static S Create(Args&&... args) noexcept(nothrow_constructible<S, Args&&...>);
	};
}
