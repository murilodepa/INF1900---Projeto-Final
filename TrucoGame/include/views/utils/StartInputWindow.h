#include <Windows.h>
#include <string>

namespace TrucoGame {
	namespace UtilsView {
		class StartInputWindow {
		private:
			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			static std::string ip;
			HWND editControl;
		public:
			int GetUserServerClientInput();
			std::string GetUserIpInput();
			int GetNumberOfPlayersInput();
		};
		
	}
}