/*
    Copyright (c) 2020 Dmitry Baryshev

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <QLabel>
#include <QSlider>

#include <stdio.h>
#include <sail/sail.h>

#include "writeoptions.h"
#include "ui_writeoptions.h"

class Q_DECL_HIDDEN WriteOptions::Private
{
public:
    QScopedPointer<Ui::WriteOptions> ui;
};

WriteOptions::WriteOptions(const QString &codecDescription, const sail_write_features *write_features, QWidget *parent)
    : QDialog(parent)
    , d(new Private)
{
    d->ui.reset(new Ui::WriteOptions);
    d->ui->setupUi(this);

    d->ui->labelCodec->setText(codecDescription);

    if (write_features->output_pixel_formats_length == 0) {
        d->ui->labelColor->setText(tr("Output color selection is not available"));
        d->ui->labelColor->setEnabled(false);
        d->ui->comboColor->setEnabled(false);
    } else {
        d->ui->labelColor->setText(tr("Output color:"));

        for (int i = 0; i < write_features->output_pixel_formats_length; i++) {
            d->ui->comboColor->addItem(sail_pixel_format_to_string(write_features->output_pixel_formats[i]),
                                       /* user data */write_features->output_pixel_formats[i]);
        }

        d->ui->comboColor->setCurrentText(sail_pixel_format_to_string(write_features->preferred_output_pixel_format));
    }

    if (write_features->compression_min == 0 && write_features->compression_max == 0) {
        d->ui->labelCompression->setText(tr("Compression levels are not available"));
        d->ui->labelCompression->setEnabled(false);
        d->ui->sliderCompression->setEnabled(false);
    } else {
        d->ui->labelCompression->setText(tr("Compression:"));
        d->ui->sliderCompression->setMinimum(write_features->compression_min);
        d->ui->sliderCompression->setMaximum(write_features->compression_max);
        d->ui->sliderCompression->setValue(write_features->compression_default);
        d->ui->labelCompressionValue->setNum(d->ui->sliderCompression->value());

        connect(d->ui->sliderCompression, &QSlider::valueChanged, [&](int value) {
            d->ui->labelCompressionValue->setNum(value);
        });
    }
}

WriteOptions::~WriteOptions()
{
}

int WriteOptions::pixelFormat() const
{
    return d->ui->comboColor->currentData().toInt();
}

int WriteOptions::compression() const
{
    return d->ui->sliderCompression->isEnabled() ? d->ui->sliderCompression->value() : -1;
}