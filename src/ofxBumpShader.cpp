#define STRINGIFY(A) #A
#include "ofxBumpShader.h"

//--------------------------------------------------------------
void ofxBumpShader::setup(string texture){
    
    // load & allocate texture map
    textureMapImage.loadImage(texture +"-texture.jpg");
    textureMap.allocate(512, 512, GL_RGB, false);
    textureMap.loadData(textureMapImage.getPixels(), 512, 512, GL_RGB);
    
    // load & allocate normal map
    normalMapImage.loadImage(texture +"-normal.jpg");
    normalMap.allocate(512, 512, GL_RGB, false);
    normalMap.loadData(normalMapImage.getPixels(), 512, 512, GL_RGB);
    
    // load & allocate diffuse map
    diffuseMapImage.loadImage(texture +"-diffuse.jpg");
    diffuseMap.allocate(512, 512, GL_RGB, false);
    diffuseMap.loadData(diffuseMapImage.getPixels(), 512, 512, GL_RGB);

    // create vertex shader
    string vertShader = STRINGIFY(
                                  
            varying vec3 light;
            varying vec3 halfvector;
            varying vec4 diffuse;
            varying vec4 ambient;
            varying vec4 globalambient;
                                    
            varying float distance;
                                    
            void main() {
                
                // get vertex vs light
                vec4 vertex = gl_ModelViewMatrix * gl_Vertex;
                vec3 aux = vec3(gl_LightSource[0].position - vertex);
                // normalize light direction
                light = normalize(aux);
                // get distance to vertex
                distance = length(aux);
                // normalize the halfvector
                halfvector = normalize(gl_LightSource[0].halfVector.xyz);
                // get diffuse, ambient & global ambient component
                diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
                ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
                globalambient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
                // texture coordinates
                gl_TexCoord[0] = gl_MultiTexCoord0;
                // vertex color
                gl_FrontColor = gl_Color;
                // transform matrix
                gl_Position = ftransform();
            
            }
    );
    
    // create fragment shader
    string fragShader = STRINGIFY(
                                  
            varying vec3 light;
            varying vec3 halfvector;
            varying vec4 diffuse;
            varying vec4 ambient;
            varying vec4 globalambient;
                                      
            varying float distance;
                                      
            uniform sampler2D textureMap;
            uniform sampler2D normalMap;
            uniform sampler2D diffuseMap;
                                  
            uniform float alpha;
                                      
            void main() {
                
                    // texture lookup
                float x = gl_TexCoord[0].s;
                float y = gl_TexCoord[0].t;
                // extract the normal from the normal map
                vec3 norm = normalize(texture2D(normalMap, vec2(x, y)).rgb * 2. - 1.);
                // ambient component is always present
                vec4 col = globalambient;
                // compute dot product between normal and normalized light
                float normDotLight = max(dot(norm, normalize(light)), 0.);
                
                // if dot product > 0
                if(normDotLight > 0.) {
                    
                    // calculate attenuation
                    float attenuation = 1. / (gl_LightSource[0].constantAttenuation + gl_LightSource[0].linearAttenuation * distance + gl_LightSource[0].quadraticAttenuation * distance * distance);
                    
                    // add diffuse component
                    col += attenuation * (diffuse * normDotLight + ambient);
                    // normalize half vector
                    vec3 HV = normalize(halfvector);
                    // compute dot product
                    float normDotHV = max(dot(norm, HV), 0.);
                    // add specular component
                    col += attenuation * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow( normDotHV, gl_FrontMaterial.shininess );
                
                }
                
                // set color
                vec4 bump = col * vec4(texture2D(textureMap, vec2(x, y)).rgb, 1.0);
                vec4 diff = vec4(texture2D(diffuseMap, vec2(x, y)).rgb, 1.0);
                
                // normal
                //gl_FragColor = bump;
                
                // additive blending
                gl_FragColor = mix(  vec4((gl_Color).rgb, alpha), vec4((bump + diff).rgb, alpha), 0.8);
                
                // screen blending
                //gl_FragColor = mix(gl_Color, vec4((bump + diff) - (bump * diff), alpha), 0.8);
            
            }
    );
    
    // setup & link shader
    shader.setupShaderFromSource(GL_VERTEX_SHADER, vertShader);
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShader);
    shader.linkProgram();

}

//--------------------------------------------------------------
void ofxBumpShader::begin(){
    
    shader.begin();
    shader.setUniformTexture("textureMap", textureMap, 0);
    shader.setUniformTexture("normalMap", normalMap, 1);
    shader.setUniformTexture("diffuseMap", diffuseMap, 2);
    shader.setUniform1f("alpha", 1);
    
}

//--------------------------------------------------------------
void ofxBumpShader::transparency(float alpha){
    
    shader.setUniform1f("alpha", alpha);
    
}

//--------------------------------------------------------------
void ofxBumpShader::end(){
    
    shader.end();
    
}
