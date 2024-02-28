#define MAKE_EMPTY_PACKET(name, protocol) \
struct [[nodiscard]] name : public BasicPacket \
{ \
	using Super = BasicPacket; \
 \
	[[nodiscard]] static consteval size_t WannabeSize() noexcept { return Super::MinSize(); } \
	[[nodiscard]] static consteval ptrdiff_t SignedWannabeSize() noexcept { return Super::SignedMinSize(); } \
 \
	constexpr name() noexcept \
		: Super((protocol), static_cast<std::int16_t>(SignedWannabeSize())) \
	{ \
	} \
 \
	[[nodiscard]] constexpr auto Serialize() const { return iconer::util::Serializes(myProtocol, mySize); } \
}
