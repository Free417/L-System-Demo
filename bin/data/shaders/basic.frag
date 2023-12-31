#version 150
in vec3 vecNormal;
in vec4 vecPosition;

out vec4 fragColor;

// this are set in the OF app
uniform vec3 uLightPosition;
uniform vec4 uMaterialColor;

void main(){
    // basic lambertian lighting
    vec3 lightDirection = normalize(vecPosition.xyz - uLightPosition);

        /*
    // Optimization comparison
    // Branching statement notably worse frame time
    if (dot(vecNormal, lightDirection) < 0)
    {
        float dProd = 0.0;
    }
    else
    {
        float dProd = dot(vecNormal, lightDirection);
    }*/

    float dProd = max(0.0, dot(vecNormal, lightDirection));

    //color
    vec4 color = uMaterialColor;
    vec4 col = vec4( vec3( dProd ) * vec3( color ), 1.0 );
    fragColor = col;
}