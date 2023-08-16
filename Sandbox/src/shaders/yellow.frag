#version 330 core    
    out vec4 fragColor;

	vec4 yellowColor = vec4(1.0, 1.0, 0.0, 1.0);
	uniform vec4 otherColor;

    void main()
    {
        fragColor = otherColor;
    }