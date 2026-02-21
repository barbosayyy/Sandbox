#pragma once

class IClient {
protected:
    IClient() = default;
public:
    virtual ~IClient() = default;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Stop() = 0;
};