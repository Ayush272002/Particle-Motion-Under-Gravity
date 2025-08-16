VENV = venv
PYTHON = $(VENV)/bin/python
PIP = $(VENV)/bin/pip

CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC
INCLUDES = $(shell $(PYTHON) -m pybind11 --includes)
EXT_SUFFIX = $(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))")

SRC = particle.cpp
TARGET = particle$(EXT_SUFFIX)
PYDEMO = demo.py
REQS = requirements.txt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

run: $(TARGET)
	$(PYTHON) $(PYDEMO)

install:
	@test -d $(VENV) || python3 -m venv $(VENV)
	$(PIP) install --upgrade pip
	$(PIP) install -r $(REQS)

clean:
	rm -f $(TARGET)
	rm -rf $(VENV)
