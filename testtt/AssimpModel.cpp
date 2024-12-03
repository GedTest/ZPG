#include "AssimpModel.h"
#include <iostream>


AssimpModel::AssimpModel(const std::string& path, Material* material, const std::string& texturePath)
    : material(material) {
    loadModel(path, texturePath);
}

AssimpModel::~AssimpModel() {
    delete this->vao;
    delete this->vbo;
    if (this->texture) {
        delete this->texture;
    }
}

void AssimpModel::loadModel(const std::string& path, const std::string& texturePath) {
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate //Converts polygons to triangles
        | aiProcess_OptimizeMeshes              // Reduces the number of submeshes
        | aiProcess_JoinIdenticalVertices       // Removes duplicate vertices
        | aiProcess_CalcTangentSpace;           // Computes tangents and bitangents

    //aiProcess_GenNormals/ai_Process_GenSmoothNormals - Generates flat/Smooth normals

    const aiScene* scene = importer.ReadFile(path, importOptions);

    if (scene) {
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);
        //Materials
        for (unsigned int i = 0; i < scene->mNumMaterials; i++)
        {
            const aiMaterial* mat = scene->mMaterials[i];
            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name %s\n", i, name.C_Str());
            aiColor4D d;
            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);
        }
        //Objects
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];
            unsigned int vertexCount = mesh->mNumVertices;
            unsigned int floatCount = vertexCount * 11; // 3 pos + 3 normal + 2 uv + 3 tangent

            float* vertices = new float[floatCount];
            std::memset(vertices, 0, floatCount * sizeof(float)); // Initialize all to zero

            for (unsigned int j = 0; j < vertexCount; j++)
            {
                unsigned int baseIndex = j * 11;

                // Position
                if (mesh->HasPositions()) {
                    vertices[baseIndex] = mesh->mVertices[j].x;
                    vertices[baseIndex + 1] = mesh->mVertices[j].y;
                    vertices[baseIndex + 2] = mesh->mVertices[j].z;
                }

                // Normal
                if (mesh->HasNormals()) {
                    vertices[baseIndex + 3] = mesh->mNormals[j].x;
                    vertices[baseIndex + 4] = mesh->mNormals[j].y;
                    vertices[baseIndex + 5] = mesh->mNormals[j].z;
                }

                // Texture coordinates
                if (mesh->HasTextureCoords(0)) {
                    vertices[baseIndex + 6] = mesh->mTextureCoords[0][j].x;
                    vertices[baseIndex + 7] = mesh->mTextureCoords[0][j].y;
                }

                // Tangent
                if (mesh->HasTangentsAndBitangents()) {
                    vertices[baseIndex + 8] = mesh->mTangents[j].x;
                    vertices[baseIndex + 9] = mesh->mTangents[j].y;
                    vertices[baseIndex + 10] = mesh->mTangents[j].z;
                }
            }

            unsigned int* pIndices = nullptr;
            if (mesh->HasFaces()) {
                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }


            this->vbo = new VertexBufferObject(vertices, floatCount * sizeof(float));
            this->vao = new VertexArrayObject();
            this->vao->enableAttribute(4);

            GLuint IBO = 0;
            glGenBuffers(1, &IBO);

            //Index Buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
            
            this->vao->unbindBuffer();

            GLuint err = glGetError();
            if (err != GL_NO_ERROR) {
                std::cout << "GL ERROR: " << err << std::endl;
            }
            indicesCount = mesh->mNumFaces * 3;

            delete[] vertices;
            delete[] pIndices;
        }
    }
    else {
        printf("Error during parsing mesh from %s : %s \n", path.c_str(), importer.GetErrorString());
    }
    this->vao->unbindBuffer();

    if (texturePath != "None") {
        this->texture = new Texture(texturePath);
    }
    return;
}

void AssimpModel::draw() const {
    this->vao->bindBuffer();
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
    this->vao->unbindBuffer();
    return;
}
