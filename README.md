# The Desk Thing

Building:

```bash
mkdir -p build && (cd build && cmake ..)
make -C build
```

Flashing:

```
picotool load -f -x ./build/src/desk_thing.uf2
```
