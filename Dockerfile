FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    python3 \
    py3-pip \
    build-base \
    ninja \
    git \
    bash


COPY . /app
    
WORKDIR /app

RUN pip3 install meson --break-system-packages
RUN meson setup builddir && ninja -C builddir

CMD ["./builddir/notes", "new", "docker"]