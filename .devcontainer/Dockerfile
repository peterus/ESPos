ARG VARIANT="3.11-bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/python:0-${VARIANT}

RUN apt-get update && apt-get install -y clang-format-13

RUN pip3 --disable-pip-version-check --no-cache-dir install platformio
