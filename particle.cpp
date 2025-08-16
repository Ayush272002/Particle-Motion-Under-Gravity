#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <random>

namespace py = pybind11;

class Particle
{
public:
    double x, y;
    double vx, vy;
    double g;
    double bounce;

    Particle(double x, double y, double vx, double vy, double g = 9.81, double bounce = 0.8)
        : x(x), y(y), vx(vx), vy(vy), g(g), bounce(bounce) {}

    void step(double dt)
    {
        vy -= g * dt;
        x += vx * dt;
        y += vy * dt;

        if (y <= 0)
        {
            y = 0;
            vy = -vy * bounce;
            static std::mt19937 gen(std::random_device{}());
            static std::uniform_real_distribution<double> dist(-0.05, 0.05);
            vx += dist(gen);  
        }
    }
};

PYBIND11_MODULE(particle, m)
{
    py::class_<Particle>(m, "Particle")
        .def(py::init<double, double, double, double, double, double>(),
             py::arg("x"), py::arg("y"), py::arg("vx"), py::arg("vy"),
             py::arg("g") = 9.81, py::arg("bounce") = 0.8)
        .def("step", &Particle::step)
        .def_readwrite("x", &Particle::x)
        .def_readwrite("y", &Particle::y)
        .def_readwrite("vx", &Particle::vx)
        .def_readwrite("vy", &Particle::vy);
}