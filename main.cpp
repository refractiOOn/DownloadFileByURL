#include <iostream>
#include <vector>
#include <Windows.h>

// Link required library
#pragma comment(lib, "urlmon.lib")

std::vector<std::wstring> parseArgs(const int argc, wchar_t **argv)
{
    std::vector<std::wstring> args;
    for (int i = 1; i < argc; ++i)
    {
        args.emplace_back(argv[i]);
    }
    return args;
}

bool download(std::wstring_view url, std::wstring_view dest)
{
    const HRESULT res = URLDownloadToFileW(nullptr, url.data(), dest.data(), 0, nullptr);
    return SUCCEEDED(res);
}

bool run(std::wstring_view path, std::wstring_view params = std::wstring_view())
{
    std::wstring command = params.empty() ? std::wstring(path)
                                          : std::wstring(path) + L" " + std::wstring(params);
    STARTUPINFOW startupInfo = { sizeof(startupInfo) };
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
    const std::vector<std::wstring> args = parseArgs(argc, argv);

    if (args.size() < 2)
    {
        std::wcerr << "No URL and destination arguments were provided" << std::endl;
        return -1;
    }
    const std::wstring url = args[0];
    const std::wstring destination = args[1];

    if (!download(url, destination))
    {
        std::wcout << "File was not loaded" << std::endl;
        return -1;
    }
    else std::wcout << "File was successfully downloaded" << std::endl;

    const std::wstring params = args.size() == 3 ? args[2] : std::wstring();
    if (!run(destination, params))
    {
        std::wcout << "Could not start specified executable" << std::endl;
        return -1;
    }

    return 0;
}
