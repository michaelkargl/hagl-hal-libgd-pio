# PlatformIO GDLib HAGL HAL

This library implements [HAGL HAL] for the [gdlib] graphics library as a [PlatformIO Library].

## Description

> **Warning**
> This library does not do anything by itself but merely provide the tools for [HAGL] to do its work. Metaphorically speaking, this HAL only provides the brush HAGL uses to draw on a gdlib canvas.

**Roughly**, to put it in OOP terms, [HAGL] relies on dependency
inversion to provide an abstraction layer between the application and the actual hardware (canvas, display). By relying on a `HAL interface` for drawing, the user can provide its own canvas. The application only has to know about `HAGL`, but no details further down. In terms of `C` this is of course merely linker magic and no actual objects or classes are involved.

```plantuml

class application {
    + draw_screen()
}

interface "HAGL HAL" as hal {
    + initialize()
    + draw_pixel()
    + flush()
}

class "ST7735 HAL" as hal_st7735 {
    + initialize_spi()
    --
    - write_spi_pixel()
    - write_spi_flush()
}

class "GD HAL" as hal_gdlib {
    + initialize_gd()
    --
    - draw_gd_pixel()
    - flush_gd_image()
}

class "HAGL" as hagl {
    + fill_circle()
    + draw_line()
    + draw_char()
}

application --> hagl: " draws using"
hal_gdlib --o hal: " implements"
hal_st7735 --o hal: " implements"
hagl ..> hal_gdlib: " indirectly\ndraws\nusing"
hagl ..> hal_st7735: "indirectly\ndraws\nusing"
hagl -> hal: " draws using"
```

## Requirements

* PlatformIO
* git symlink support

```git
git submodule foreach --recursive 'git submodule init && git submodule update'
```

## Example

Check out the sample application in the [samples] folder.

![](./examples/drawing-sample.gif)


[PlatformIO Library]: https://docs.platformio.org/en/latest/manifests/library-json/index.html
[PlatformIO]: https://platformio.org/
[HAGL]: https://github.com/tuupola/hagl.git
[HAGL HAL]: https://github.com/tuupola/hagl#backend
[library.json]: ./library.json
[gdlib]: https://libgd.github.io/
[samples]: ./examples