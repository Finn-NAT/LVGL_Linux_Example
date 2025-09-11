# Sử dụng Ubuntu 20.04 (cùng môi trường host)
FROM ubuntu:22.04

# Thiết lập môi trường không hỏi khi cài đặt
ENV DEBIAN_FRONTEND=noninteractive

# Cài công cụ build và SDL2 (tùy chọn)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    make \
    pkg-config \
    git \
    libsdl2-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Copy toàn bộ source code vào container
WORKDIR /app
COPY . /app

# Biến ARG để chọn build SDL hay Framebuffer
ARG BUILD_SDL=0
ARG BUILD_ARM=0


WORKDIR /app/Linux_LVGL_Examples
RUN mkdir -p build && bash -lc '\
    cd build && \
    if [ "$BUILD_SDL" = "1" ] && [ "$BUILD_ARM" = "1" ]; then \
      cmake -DSDL=ON -DARM=ON ..; \
    elif [ "$BUILD_SDL" = "1" ] && [ "$BUILD_ARM" = "0" ]; then \
      cmake -DSDL=ON -DARM=OFF ..; \
    elif [ "$BUILD_SDL" = "0" ] && [ "$BUILD_ARM" = "1" ]; then \
      cmake -DSDL=OFF -DARM=ON ..; \
    else \
      cmake -DSDL=OFF -DARM=OFF ..; \
    fi && \
    make -j$(nproc) \
'

CMD ["sh", "-c", "cp /app/Linux_LVGL_Examples/build/LVGL_Linux_Example /output/LVGL_Linux_Example"]