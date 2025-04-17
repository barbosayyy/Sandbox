#pragma once

#include "Renderable.h"

namespace SbEngine{
    
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
        Square();
        ~Square();

        void Draw(Renderer* renderer) override;
    protected:
        void Create() override;
    };

    class Plane : public Renderable{
    public:
        Plane(float x, float y, float z);
        Plane();
        ~Plane();

        void Draw(Renderer* renderer) override;
    protected:
        void Create() override;
    };
}

