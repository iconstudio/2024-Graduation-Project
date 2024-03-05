module Demo.Framework;

bool
demo::Framework::OnCreateGame(iconer::app::User& user)
{
	return false;
}

void
demo::Framework::OnFailedToCreateGame(iconer::app::User& user)
noexcept
{
}
