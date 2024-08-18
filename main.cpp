#include <Windows.h>

#include <iostream>
#include <time.h>
#include <thread>
#include <filesystem>

int main(int argc, char * argv[]){
    time_t start = time(0);
    HWND gameWindow = nullptr;
    HWND menuWindow = FindWindowA("Engine", "Game Menu");
    HWND launcherWindow = FindWindowA("Engine", "Half-Life: Alyx NoVR Launcher");
    if (argc > 1) {
        gameWindow = FindWindowA("SDL_app", "Half-Life: Alyx");
        std::string arg1 = argv[1];
        if (arg1 == "exec") {
            SendMessage(gameWindow, WM_KEYDOWN, VK_PAUSE, 0);
            SendMessage(gameWindow, WM_KEYUP, VK_PAUSE, 0);
        } else if (arg1 == "style") {
            const LONG_PTR oldExStyle = GetWindowLongPtr(menuWindow, GWL_EXSTYLE);
            SetWindowLongPtr(menuWindow, GWL_EXSTYLE, oldExStyle | WS_EX_NOACTIVATE);
        } else if (arg1 == "focusgame") {
            SetForegroundWindow(gameWindow);
        } else if (arg1 == "focuslauncher") {
            SetForegroundWindow(launcherWindow);
        } else if (arg1 == "update") {
            int error = -1;
            while (error != 0) {
#ifdef _WIN32
                error = remove("HLA-NoVR-Launcher.exe");
#elif unix

#endif
            }
#ifdef _WIN32
            std::filesystem::rename("HLA-NoVR-Launcher.exe.update", "HLA-NoVR-Launcher.exe");

            STARTUPINFO si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));
            CreateProcess(NULL, const_cast<LPSTR>("HLA-NoVR-Launcher.exe"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
#elif unix

#endif
        }
    } else {
        RECT rect;
        while (gameWindow == nullptr) {
            if (difftime(time(0), start) > 120) {
               std:: cout << "exit" << std::endl;
                return 0;
            } else {
                gameWindow = FindWindowA("SDL_app", "Half-Life: Alyx");
            }
        }
        SetWindowLongPtr(menuWindow, GWLP_HWNDPARENT, (LONG_PTR)gameWindow);
        SetForegroundWindow(gameWindow);
        while (GetClientRect(gameWindow, &rect)) {
            ClientToScreen(gameWindow, reinterpret_cast<POINT*>(&rect.left));
            ClientToScreen(gameWindow, reinterpret_cast<POINT*>(&rect.right));
            std::cout << "geometry:" << rect.left << ":" << rect.top << ":" << (rect.right - rect.left) << ":" << (rect.bottom - rect.top) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::cout << "exit" << std::endl;
    }
    return 0;
}
