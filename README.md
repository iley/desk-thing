# The Desk Thing

Building:

```bash
mkdir -p build && cd build
cmake ..
make
```

Flashing:

```
picotool load -f -x ./build/src/desk_thing.uf2
```
