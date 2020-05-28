Table of Contents
=================

   * [SAIL Frequently Asked Questions (FAQ)](#sail-frequently-asked-questions-faq)
      * [How old is SAIL?](#how-old-is-sail)
      * [Is SAIL cross-platform?](#is-sail-cross-platform)
      * [How many image formats do you plan to implement?](#how-many-image-formats-do-you-plan-to-implement)
      * [I have questions, issues, or proposals](#i-have-questions-issues-or-proposals)
      * [Does SAIL provide simple one-line APIs?](#does-sail-provide-simple-one-line-apis)
      * [How can point SAIL to a different plugins location?](#how-can-point-sail-to-a-different-plugins-location)
      * [What pixel formats SAIL is able to read?](#what-pixel-formats-sail-is-able-to-read)
      * [What pixel formats SAIL is able to output after reading an image file?](#what-pixel-formats-sail-is-able-to-output-after-reading-an-image-file)
      * [What pixel formats SAIL is able to write?](#what-pixel-formats-sail-is-able-to-write)
      * [How can I read an image and output pixels in different formats?](#how-can-i-read-an-image-and-output-pixels-in-different-formats)
      * [Does SAIL support animated and multi-paged images?](#does-sail-support-animated-and-multi-paged-images)
      * [Does SAIL support reading from memory?](#does-sail-support-reading-from-memory)
      * [Are there any C/C++ examples?](#are-there-any-cc-examples)
      * [Are there any bindings to other programming languages?](#are-there-any-bindings-to-other-programming-languages)

# SAIL Frequently Asked Questions (FAQ)

## How old is SAIL?

SAIL is a rebranded ksquirrel-libs, enchanced and with high-level APIs. Ksquirrel-libs was a set of C++ image codecs
for the KSquirrel image viewer. See [http://ksquirrel.sourceforge.net](http://ksquirrel.sourceforge.net).

Technically, SAIL was founded in 2003 making it one of the oldest image decoding libraries.

## Is SAIL cross-platform?

Yes. It's written in pure C11 and is highly portable. However, only the Windows and Linux platforms
are currently supported. Pull requests to support more platforms are highly welcomed.

## How many image formats do you plan to implement?

Ksquirrel-libs supported around 60 image formats. I don't plan to port all of them. However,
the most popular image formats will be definitely ported from ksquirrel-libs.

## I have questions, issues, or proposals

Opening a GitHub [issue](https://github.com/smoked-herring/sail/issues) is the preferred way
of communicating and solving problems.

Pull requests are always welcomed.

## Does SAIL provide simple one-line APIs?

Yes. SAIL provides four levels of APIs, depending on your needs: `junior`, `advanced`, `deep diver`, and `technical diver`.
See [EXAMPLES](EXAMPLES.md) for more.

## How can point SAIL to a different plugins location?

Set `SAIL_PLUGINGS_PATH` environment variable to a desired location.

## What pixel formats SAIL is able to read?

SAIL codecs (plugins) always try to support as much input pixel formats as possible. The list of
pixel formats that can be read by SAIL is plugin-specific and is not publicly available.

## What pixel formats SAIL is able to output after reading an image file?

SAIL is always able to output the `SOURCE`, `BPP24-RGB`, and `BPP32-RGBA` pixel formats after reading. Some plugins may
support even more output pixel formats. Use `sail_plugin_info_from_extension() -> plugin_info -> read_features ->
output_pixel_formats` to determine the list of supported output pixel formats per plugin.

Use the `SOURCE` pixel format to request the image pixel data as is. For example, one may want to work
with CMYK pixels in a print image without converting them to RGB.

## What pixel formats SAIL is able to write?

SAIL codecs (plugins) always try to support as much output pixel formats as possible. The list of
pixel formats that can be written by SAIL is plugin-specific and is publicly available in every
.plugin.info file. It can be accessed through `sail_plugin_info_from_extension() -> plugin_info -> write_features ->
pixel_formats_mapping_node`.

`pixel_formats_mapping_node` is a map-like linked list describing what pixel formats SAIL is able to write from
the given input pixel format. Consider the following structure of `pixel_formats_mapping_node`:

| Input pixel format    | Output pixel formats                      |
| --------------------- | ----------------------------------------- |
| `BPP8-GRAYSCALE`      | `SOURCE`                                  |
| `BPP24-RGB`           | `SOURCE`, `BPP24-YCBCR`, `BPP8-GRAYSCALE` |

The structure above has the following meaning:

1. When a user has an image in `BPP8-GRAYSCALE` format, he/she is able to save it as a `BPP8-GRAYSCALE` (`SOURCE`) image only
2. When a user has an image in `BPP24-RGB` format, he/she is able to save it as a `BPP24-RGB` (`SOURCE`),
   `BPP24-YCBCR`, and `BPP8-GRAYSCALE` image

The `SOURCE` output pixel format is always supported.

## How can I read an image and output pixels in different formats?

Use read options for that. For example:

```C
sail_plugin_info_from_extension(...);

sail_read_options_from_features(...);

read_options->output_pixel_format = SAIL_PIXEL_FORMAT_BPP32_RGBA;

sail_start_reading_file_with_options(...);
```

The `SOURCE`, `BPP24-RGB`, and `BPP32-RGBA` output pixel formats are always supported.
See [EXAMPLES](EXAMPLES.md) for more.

## Does SAIL support animated and multi-paged images?

Yes. Just continue reading the image file until the reading functions return `0`.
If no more frames are available, the reading functions return `SAIL_NO_MORE_FRAMES`.

## Does SAIL support reading from memory?

Yes. SAIL supports reading/writing from/to files and memory. For technical divers,
it's also possible to use custom I/O sources.

See `sail_start_reading_file()`, `sail_start_reading_mem()`, and `sail_start_reading_io()`.

## Are there any C/C++ examples?

Yes. See [EXAMPLES](EXAMPLES.md) for more.

## Are there any bindings to other programming languages?

Yes. Currently SAIL supports the following bindings:

1. C++

Pull requests to support more programming languages are highly welcomed.