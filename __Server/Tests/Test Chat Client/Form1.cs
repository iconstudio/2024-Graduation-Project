using System.Diagnostics.CodeAnalysis;
using System.Net;
using System.Net.Sockets;

namespace Test_Chat_Client
{
	public partial class Form1 : Form
	{
		private Panel currentPage;

		private readonly Socket mySocket;
		private readonly IPEndPoint serverEndpoint;
		private const ushort severPort = 10000;
		private bool isConnecting;

		private const int bufferSize = 256;
		byte[] recvBuffer;
		int recvBytes;
		byte[] sendBuffer;
		private const int maxChatCount = 40;
		private List<string> chatMessages;

		private bool Connected => mySocket != null && mySocket.Connected;

		private void BeginSignIn()
		{
			lock (mySocket)
			{
				if (!isConnecting)
				{
					isConnecting = true;

					var r = mySocket.BeginConnect(serverEndpoint, EndSignIn, null);
					if (r != null)
					{
						if (r.CompletedSynchronously)
						{
							ChangePageToChatting();
							isConnecting = false;
						}
					}
				}
			}
		}
		private void EndSignIn(IAsyncResult result)
		{
			lock (mySocket)
			{
				mySocket.EndConnect(result);
				isConnecting = false;

				if (result.IsCompleted)
				{
					ChangePageToChatting();
				}
			}
		}
		private void BeginSignOut()
		{
			lock (mySocket)
			{
				if (Connected)
				{
					mySocket.Shutdown(SocketShutdown.Both);

					mySocket.BeginDisconnect(true, EndSignOut, null);
				}
				else
				{
					ChangePageToSignIn();
				}
			}
		}
		private void EndSignOut(IAsyncResult result)
		{
			lock (mySocket)
			{
				mySocket.EndDisconnect(result);

				ChangePageToSignIn();
				mySocket.Close();
			}
		}
		private void BeginReceive()
		{
			lock (mySocket)
			{
				var recv = mySocket.BeginReceive(recvBuffer, recvBytes, bufferSize - recvBytes, SocketFlags.None, EndReceive, null);
				if (recv != null)
				{
					if (recv.IsCompleted)
					{
						mySocket.EndReceive(recv);
					}
				}
			}
		}
		private void EndReceive(IAsyncResult result)
		{
			lock (mySocket)
			{
				var bytes = mySocket.EndReceive(result);

				if (0 < bytes)
				{
					recvBytes += bytes;
					var span = recvBuffer.Take(recvBytes);

					var str = span.Cast<char>();
					var msg = str.ToString();
					if (msg is null)
					{
						throw new Exception("Invaild message");
					}
					else
					{
						if (maxChatCount <= chatMessages.Count)
						{
							chatMessages.RemoveAt(0);
						}
						chatMessages.Add(msg);
					}

					// restart
					BeginReceive();
				}
				else
				{
					throw new Exception("Receive Error");
				}
			}
		}
		private void AddChatMessage(string msg)
		{
			chatMessages.Add(msg);
		}
		private void AddMember(string msg)
		{
			memberListBox.Items.Add(msg);
		}

		private void Initialize()
		{
			signInPage.VisibleChanged += (object? sender, EventArgs e) =>
			{
				ChangeVisible(signInMenuItem, true);
				ChangeVisible(signOutMenuItem, false);
				chatMessages.Clear();
			};
			chatPage.VisibleChanged += (object? sender, EventArgs e) =>
			{
				ChangeVisible(signInMenuItem, false);
				ChangeVisible(signOutMenuItem, true);
				BeginReceive();
			};

			recvBuffer = new byte[bufferSize];
			sendBuffer = new byte[bufferSize];
			chatMessages = new()
			{
				Capacity = 40
			};

			ChangePageToSignIn();
		}

		private void ChangeCurrentPage([NotNull] in Panel page)
		{
			if (currentPage != null)
			{
				ChangeVisible(currentPage, false);
			}
			currentPage = page;
			ChangeVisible(page, true);
		}
		private void ChangePageToSignIn()
		{
			ChangeCurrentPage(signInPage);
		}
		private void ChangePageToChatting()
		{
			ChangeCurrentPage(chatPage);
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Initialize();
		}
		private void signInButton_Click(object sender, EventArgs e)
		{
			BeginSignIn();
		}
		private void 로그인ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			BeginSignIn();
		}
		private void signOutMenuItem_Click(object sender, EventArgs e)
		{
			BeginSignOut();
		}
		private void 설정ToolStripMenuItem_Click(object sender, EventArgs e)
		{

		}
		private void 닫기ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}

		public Form1()
		{
			InitializeComponent();

			mySocket = new(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp)
			{
				ExclusiveAddressUse = false,
				Blocking = false,
			};
			mySocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
			serverEndpoint = new(IPAddress.Loopback, severPort);
		}
		~Form1()
		{
			mySocket.Dispose();
		}

		private static void ChangeVisible(Control? control, bool visible)
		{
			if (control is not null)
			{
				if (control.InvokeRequired)
				{
					control.Invoke(new MethodInvoker(() => UncheckedSetVisible(control, visible)));
				}
				else
				{
					UncheckedSetVisible(control, visible);
				}
			}
		}
		private static void ChangeVisible(ToolStripMenuItem? item, bool visible)
		{
			if (item is not null)
			{
				if (item.Owner?.InvokeRequired ?? false)
				{
					item.Owner.Invoke(new MethodInvoker(() => item.Visible = visible));
				}
				else
				{
					item.Visible = visible;
				}
			}
		}
		private static void UncheckedSetVisible([NotNull] Control control, in bool visible)
		{
			control.Visible = visible;
		}
	}
}
