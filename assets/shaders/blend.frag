uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float alpha;


void main()
{
    // Get the texture coordinate
    vec2 uv = gl_TexCoord[0].xy;

    // Sample both textures at the same coordinate
    vec4 color1 = texture2D(tex1, uv);
    vec4 color2 = texture2D(tex2, uv);

    // Interpolate (blend) based on alpha
    gl_FragColor = mix(color1, color2, alpha);
}