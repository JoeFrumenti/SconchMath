#include "ShaderCollection.h"

ShaderCollection::ShaderCollection() {
	shaders["Model"] = new Shader("C:/Users/joefr/source/repos/SconchMath/modelShader.vs", "C:/Users/joefr/source/repos/SconchMath/modelShader.fs");
	shaders["Text"] = new Shader("C:/Users/joefr/source/repos/SconchMath/textShader.vs", "C:/Users/joefr/source/repos/SconchMath/textShader.fs");
}
Shader* ShaderCollection::getShader(std::string s) {
	return shaders[s];
}