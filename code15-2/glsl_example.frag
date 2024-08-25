varying vec3 vertex_normal, light_vector;
varying float distance;

void main() {
    vec3 Kd = vec3(1.0, 1.0, 1.0);
    vec3 Id = vec3(gl_LightSource[0].diffuse);
    vec3 Dr;
    for (int i=0; i<3; i++)
        Dr[i] = Kd[i] * Id[i] * dot(light_vector, vertex_normal) / (0.3 * distance);
    gl_FragColor = vec4(Dr[0], Dr[1], Dr[2], 1.0);
}
