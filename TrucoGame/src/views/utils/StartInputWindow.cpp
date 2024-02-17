#include "..\..\..\include\views\utils\StartInputWindow.h"

namespace TrucoGame {
    namespace UtilsView {
        LRESULT CALLBACK StartInputWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            switch (uMsg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            case WM_COMMAND: {
                // Handle button click
                if (LOWORD(wParam) == 2) {
                    char buffer[256];
                    // Get text from the edit control
                    if (GetWindowText(GetDlgItem(hwnd, 1), buffer, sizeof(buffer))) {
                        PostQuitMessage(0);
                    }
                    
                }
                return 0;
            }

            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
            }
        }

        int StartInputWindow::GetUserServerClientInput() {
            std::string popupMessage = "Quer iniciar uma nova partida?";
            int result = MessageBoxA(NULL, "Sim: Server\nNão: Client", popupMessage.c_str(), MB_YESNO);

            switch (result)
            {
            case IDYES:
                return 1;
            case IDNO:
                return 2;
            }
        }

        std::string StartInputWindow::GetUserIpInput()
        {
            const char CLASS_NAME[] = "GetServerIp";

            WNDCLASS wc = {};

            wc.lpfnWndProc = WindowProc;
            wc.hInstance = GetModuleHandle(nullptr);
            wc.lpszClassName = CLASS_NAME;

            RegisterClass(&wc);

            // Get screen dimensions
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);

            // Calculate window position to center it on the screen
            int windowWidth = 500;
            int windowHeight = 200;
            int x = (screenWidth - windowWidth) / 2;
            int y = (screenHeight - windowHeight) / 2;

            // Create the window
            HWND hwnd = CreateWindowEx(
                0,                               // Optional window styles
                CLASS_NAME,                      // Window class name
                "Get Server IP Address",                 // Window title
                WS_OVERLAPPEDWINDOW,             // Window style

                // Size and position
                x, y, 350, 100,

                nullptr,        // Parent window
                nullptr,        // Menu
                GetModuleHandle(nullptr), // Instance handle
                nullptr         // Additional application data
            );

            if (hwnd == nullptr) {
                return 0;
            }

            // Create an edit control for string input
            editControl = CreateWindowEx(
                0, "EDIT", "127.0.0.1", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                10, 10, 200, 25, hwnd, (HMENU)1, GetModuleHandle(nullptr), nullptr);

            // Create a button for user interaction
            HWND button = CreateWindow("BUTTON", "Ok", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                220, 10, 100, 30, hwnd, (HMENU)2, GetModuleHandle(nullptr), nullptr);

            // Show the window
            ShowWindow(hwnd, SW_SHOWDEFAULT);
            UpdateWindow(hwnd);

            // Message loop
            MSG msg = {};
            while (GetMessage(&msg, nullptr, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            char buffer[256];
            // Get text from the edit control
            GetWindowText(editControl, buffer, sizeof(buffer));
            std::string editText = buffer;

            DestroyWindow(hwnd);
            return editText;
        }

        int StartInputWindow::GetNumberOfPlayersInput() {
            const char CLASS_NAME[] = "GetNumberOfPlayers";

            WNDCLASS wc = {};

            wc.lpfnWndProc = WindowProc;
            wc.hInstance = GetModuleHandle(nullptr);
            wc.lpszClassName = CLASS_NAME;

            RegisterClass(&wc);

            // Get screen dimensions
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);

            // Calculate window position to center it on the screen
            int windowWidth = 500;
            int windowHeight = 200;
            int x = (screenWidth - windowWidth) / 2;
            int y = (screenHeight - windowHeight) / 2;

            // Create the window
            HWND hwnd = CreateWindowEx(
                0,                               // Optional window styles
                CLASS_NAME,                      // Window class name
                "Get Number of players",                 // Window title
                WS_OVERLAPPEDWINDOW,             // Window style

                // Size and position
                x, y, 350, 100,

                nullptr,        // Parent window
                nullptr,        // Menu
                GetModuleHandle(nullptr), // Instance handle
                nullptr         // Additional application data
            );

            if (hwnd == nullptr) {
                return 0;
            }

            // Create an edit control for string input
            editControl = CreateWindowEx(
                0, "EDIT", "1", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                10, 10, 200, 25, hwnd, (HMENU)1, GetModuleHandle(nullptr), nullptr);

            // Create a button for user interaction
            HWND button = CreateWindow("BUTTON", "Ok", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                220, 10, 100, 30, hwnd, (HMENU)2, GetModuleHandle(nullptr), nullptr);

            // Show the window
            ShowWindow(hwnd, SW_SHOWDEFAULT);
            UpdateWindow(hwnd);

            // Message loop
            MSG msg = {};
            while (GetMessage(&msg, nullptr, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            char buffer[256];
            // Get text from the edit control
            GetWindowText(editControl, buffer, sizeof(buffer));
            std::string editText = buffer;
            int result = stoi(editText);

            DestroyWindow(hwnd);
            return result;
        }
    }
}