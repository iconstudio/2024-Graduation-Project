export module Net.IObject;

export namespace net
{
	class IObject
	{
	public:
		constexpr IObject() noexcept = default;
		virtual constexpr ~IObject() noexcept = default;

		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update([[maybe_unused]] float delta_time) = 0;
	};
}
