#pragma once

#include "Renderable.h"

namespace Sandbox{
    
    class Cube : public Renderable {
    public:
        Cube(float x, float y, float z);
        Cube();

        ~Cube();

        void Draw(Renderer* renderer) override;
    private:
        void Create() override;
    };

    class Square : public Renderable{
    public:
        Square(float x, float y, float z);
        ~Square();

        void Draw(Renderer* renderer) override;
    protected:
        void Create() override;
    };

    class Square2 : public Renderable {
    public:
        Square2(float x, float y, float z);
        ~Square2();

        void Draw(Renderer* renderer) override;
    private:
        void Create() override;
        std::vector<float> _vertices;
        std::vector<unsigned int> _indices;
    };
}

