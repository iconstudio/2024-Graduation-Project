export module Iconer.Application.BorrowedSendContext;
import Iconer.Application.IContext;
import Iconer.Application.BlobSendContext;
import <utility>;

export namespace iconer::app
{
	class [[nodiscard]] BorrowedSendContext : public BlobSendContext
	{
	public:
		using Super = BlobSendContext;

		using Super::Super;
	};
}
