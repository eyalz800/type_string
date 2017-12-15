type\_string
=============
Creating a type from a string in standard C++.

Abstract
--------
Sometimes we wish we could treat every string as a different type,
for many different and creative reasons.

There is a GNU extension that implements a special
user defined literal operator template for strings, which
we can use to achieve this goal ideomatically.

However, this extension is not available on some compilers,
including Microsoft's own Visual Studio.

Motivation
----------
Provide a reliable, standard C++ way, to create a type
from any constant string, in a simple and efficient way.

Example
-------
The following example makes the compiler issue a diagnostic with the resulting type
using the class template `print`.

```cpp
#include "type_string.h"

template <typename...>
class print;

int main()
{
    // decltype(string) == zpp::type_string<char, 'H', 'e', 'l', 'l', 'o', ' ', 'W',
    //     'o', 'r', 'l', 'd'>>
    auto string = ZPP_MAKE_TYPE_STRING("Hello World");
    print<decltype(string)>();
}
```

Possible output:
```
main.cpp:11:2: error: implicit instantiation of undefined template 'print<zpp::type_string<char, 'H', 'e', 'l', 'l', 'o', ' ', 'W',
      'o', 'r', 'l', 'd'> >'
        print<decltype(string)>();
        ^
main.cpp:4:7: note: template is declared here
class print;
      ^
```

