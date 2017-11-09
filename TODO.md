# TODO

## Win32 Port

[ ] Check all replacements from `long` to `int64_t`
[ ] Check `util.cpp:enlargeStack()`
[x] Color console output (`def.h`), using ANSI sequences is possible on WIN10 > 14393

## Notes for Win32 Programming

- Don't assume `using namespace std;`
- use `using namespace std;` after `#include`
- MSVC does not support arrays with non static sizes (C99 extension)
- If `#include <windows>` set -DNOMINMAX to remove the `min()` and `max()` macros
- Do not use uint, it is a GNU extension
- Console Color in Windows is changed with https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute
  New Version of WIN10 can do this w/o special calls: https://docs.microsoft.com/en-us/windows/console/setconsolemode
  (`ENABLE_VIRTUAL_TERMINAL_INPUT`)
