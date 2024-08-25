varying vec3 vertex_normal, light_vector;
varying float distance;

void main() {
    vertex_normal = normalize(gl_Normal);
    gl_Position = ftransform();
    vec3 vertex_position;
    vertex_position.x = gl_Position.x / gl_Position.w;
    vertex_position.y = gl_Position.y / gl_Position.w;
    vertex_position.z = gl_Position.z / gl_Position.w;
    vec3 light_position;
    light_position.x = gl_LightSource[0].position.x / gl_LightSource[0].position.w;
    light_position.y = gl_LightSource[0].position.y / gl_LightSource[0].position.w;
    light_position.z = gl_LightSource[0].position.z / gl_LightSource[0].position.w;
    light_vector = normalize(light_position);
    distance = distance(vertex_position, light_position);
}
