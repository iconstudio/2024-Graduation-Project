export module Net.IResourcePool;
import <memory_resource>;

export namespace net
{
	template<typename T>
	class IResourcePool
	{
	public:
		[[nodiscard]] virtual const T* At(const size_t& index) = 0;
		[[nodiscard]] virtual const T* const At(const size_t& index) const = 0;
		[[nodiscard]] virtual bool TryGet(const size_t& index, const T* obj) noexcept = 0;
		[[nodiscard]] virtual bool TryGet(const size_t& index, const T* obj) const noexcept = 0;
		[[nodiscard]] virtual const T* GetBuffer() noexcept = 0;
		[[nodiscard]] virtual const T* const GetBuffer() const noexcept = 0;

		virtual const T* operator[](const size_t& index) = 0;
		virtual const T* const operator[](const size_t& index) const = 0;
	};
}
