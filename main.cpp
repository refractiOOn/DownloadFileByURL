#include <iostream>
#include <Windows.h>

// Link required library
#pragma comment(lib, "urlmon.lib")

bool download(std::wstring_view url, std::wstring_view dest)
{
    const HRESULT res = URLDownloadToFileW(nullptr, url.data(), dest.data(), 0, nullptr);
    return SUCCEEDED(res);
}

bool run(std::wstring_view path, std::wstring_view params)
{
    std::wstring command = std::wstring(path) + L" " + std::wstring(params);
    STARTUPINFOW startupInfo = { sizeof(startupInfo )};
    PROCESS_INFORMATION procInfo;

    if (!CreateProcessW(nullptr, command.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &startupInfo, &procInfo))
    {
        return false;
    }

    WaitForSingleObject(procInfo.hProcess, INFINITE);
    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);

    return true;
}

int wmain(int argc, wchar_t **argv)
{
    const std::wstring url = L"https://zoom.us/client/latest/ZoomInstaller.exe";
    const std::wstring destination = L"C:/Users/Refraction/Downloads/zoom_installer.exe";

    if (!download(url, destination))
    {
        std::wcout << "File was not loaded" << std::endl;
        return -1;
    }
    else std::wcout << "File was successfully downloaded" << std::endl;

    if (!run(destination, L"-h"))
    {
        std::wcout << "Could not start specified executable" << std::endl;
    }

    return 0;
}
