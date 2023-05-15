## Sample Qt 5.15 (QtWidgets + QML) CMake hello world

Sample QtWidgets application *with* embedded QML (+extras):

- C++ 17, Qt5.15, CMake, CCache
- QtWidgets & QtQuick
- Main and About window
- Embedded Qt resource (QRC) 
- static utils class
- Config directory + config file

See also:

- Qt5 QtWidgets template: [qt5-widgets-cmake-hello-world](https://github.com/kroketio/qt5-widgets-cmake-hello-world)
- Qt5 QML template: [qt5-qml-cmake-hello-world](https://github.com/kroketio/qt5-qml-cmake-hello-world)
- Qt5 Widgets + QML template (this): [qt5-widgets-qml-cmake-hello-world](https://github.com/kroketio/qt5-widgets-qml-cmake-hello-world)

### Installation (Linux / Mac OS)

To build, run:

```text
cmake -Bbuild .
make -Cbuild -j4
```

And if you have Qt installed in a custom directory, use this CMake command instead:

```text
cmake -DCMAKE_PREFIX_PATH="/home/user/qt5.15/gcc_64" -Bbuild .
```

Which will produce the dynamically linked executable `build/bin/hello`
