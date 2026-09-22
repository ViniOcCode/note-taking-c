FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    python3 \
    py3-pip \
    build-base \
    ninja \
    git \
    vim \
    bash

WORKDIR /app

RUN pip3 install meson --break-system-packages

COPY . .

RUN meson setup builddir && meson compile -C builddir

ENV EDITOR=vim

ENTRYPOINT ["/app/builddir/notes"]
