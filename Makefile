# Makefile
#
# Makefile completo separando os diferentes elementos da aplicacao
# como codigo (src), cabecalhos (include), executaveis (build),
# bibliotecas (lib), etc. Cada elemento e alocado em uma pasta
# especifica, organizando melhor o codigo fonte.
#
# Algumas variaveis sao usadas com significado especial:
#
# $@ nome do alvo (target)
# $^ lista com os nomes de todos os pre-requisitos sem duplicatas
# $< nome do primeiro pre-requisito
#

# Comandos do sistema operacional
# Linux: rm -rf
# Windows: cmd //C del
RM = rm -rf

# Compilador
CC=g++

# Variaveis para os subdiretorios
INC_DIR=include
SRC_DIR=src
OBJ_DIR=build
#BIN_DIR=bin
DOC_DIR=doc

# Opcoes de compilacao
CFLAGS=-Wall -pedantic -std=c++11 -I. -I$(INC_DIR)

# Garante que os alvos desta lista nao sejam confundidos com arquivos
# de mesmo nome
.PHONY: all init clean debug doxy doc

# Define o alvo (target) para a compilacao completa e os alvos
# de dependencia. Ao final da compilacao, remove os arquivos objeto.
all: init render

debug: CFLAGS += -g -O0
debug: all

# Alvo (target) para a criação da estrutura de diretorios
# necessaria para a geracao dos arquivos objeto
init:
	@mkdir -p $(BIN_DIR)/
	@mkdir -p $(OBJ_DIR)/

# Alvo (target) para a construcao do executavel create1
# Define o arquivo build/render.o como dependencia
render: $(OBJ_DIR)/main.o $(OBJ_DIR)/util.o $(OBJ_DIR)/image.o $(OBJ_DIR)/blinnPhongShader.o $(OBJ_DIR)/lambertianShader.o $(OBJ_DIR)/distantLight.o $(OBJ_DIR)/sphere.o $(OBJ_DIR)/raytracer.o  $(OBJ_DIR)/ambientLight.o $(OBJ_DIR)/DiffuseShader.o $(OBJ_DIR)/MetalMaterial.o $(OBJ_DIR)/LambertianMaterial.o $(OBJ_DIR)/RecursiveShader.o
	$(CC) $(CFLAGS) -o render $^
	@echo "Executavel ./render criado\n"

# Define o arquivo src/main.cpp como dependencia
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/raytracer.h $(INC_DIR)/vec3.h $(INC_DIR)/ray.h $(INC_DIR)/sphere.h $(INC_DIR)/camera.h $(INC_DIR)/object.h $(INC_DIR)/image.h $(INC_DIR)/scene.h $(INC_DIR)/shader.h $(INC_DIR)/light.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/util.cpp como dependencia
$(OBJ_DIR)/util.o: $(SRC_DIR)/util.cpp $(INC_DIR)/util.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/image.cpp como dependencia
$(OBJ_DIR)/image.o: $(SRC_DIR)/image.cpp $(INC_DIR)/image.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/raytrace.cpp como dependencia
$(OBJ_DIR)/raytracer.o: $(SRC_DIR)/raytracer.cpp $(INC_DIR)/ray.h $(INC_DIR)/raytracer.h
	$(CC) -c $(CFLAGS) -o $@ $<


##### SHADERS
# Define o arquivo src/blinnPhongShader.cpp como dependencia
$(OBJ_DIR)/blinnPhongShader.o: $(SRC_DIR)/blinnPhongShader.cpp $(INC_DIR)/shader.h $(INC_DIR)/vec3.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/lambertianShader.cpp como dependencia
$(OBJ_DIR)/lambertianShader.o: $(SRC_DIR)/lambertianShader.cpp $(INC_DIR)/shader.h $(INC_DIR)/vec3.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/DiffuseShader.cpp como dependencia
$(OBJ_DIR)/DiffuseShader.o: $(SRC_DIR)/DiffuseShader.cpp $(INC_DIR)/shader.h $(INC_DIR)/util.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/RecursiveShader.cpp como dependencia
$(OBJ_DIR)/RecursiveShader.o: $(SRC_DIR)/RecursiveShader.cpp $(INC_DIR)/shader.h
	$(CC) -c $(CFLAGS) -o $@ $<


#### LIGHTS
# Define o arquivo src/ambientLight.cpp como dependencia
$(OBJ_DIR)/ambientLight.o: $(SRC_DIR)/ambientLight.cpp $(INC_DIR)/light.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/distantLight.cpp como dependencia
$(OBJ_DIR)/distantLight.o: $(SRC_DIR)/distantLight.cpp $(INC_DIR)/light.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/pontualLight.cpp como dependencia
$(OBJ_DIR)/pontualLight.o: $(SRC_DIR)/pontualLight.cpp $(INC_DIR)/light.h
	$(CC) -c $(CFLAGS) -o $@ $<

#### Object
# Define o arquivo src/sphere.cpp como dependencia
$(OBJ_DIR)/sphere.o: $(SRC_DIR)/sphere.cpp $(INC_DIR)/sphere.h
	$(CC) -c $(CFLAGS) -o $@ $<

#### Material
# Define o arquivo src/LambertianMaterial.cpp como dependencia
$(OBJ_DIR)/LambertianMaterial.o: $(SRC_DIR)/LambertianMaterial.cpp $(INC_DIR)/material.h $(INC_DIR)/util.h $(INC_DIR)/object.h $(INC_DIR)/vec3.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Define o arquivo src/MetalMaterial.cpp como dependencia
$(OBJ_DIR)/MetalMaterial.o: $(SRC_DIR)/MetalMaterial.cpp $(INC_DIR)/material.h $(INC_DIR)/util.h  $(INC_DIR)/object.h $(INC_DIR)/vec3.h
	$(CC) -c $(CFLAGS) -o $@ $<
# Alvo (target) para a geração automatica de documentacao
# usando o Doxygen. Sempre remove a documentacao anterior (caso exista)
# e gera uma nova.
doxy:
	doxygen -g

doc:
	$(RM) $(DOC_DIR)/*;mkdir -p $(DOC_DIR)/
	doxygen

# Alvo (target) usado para limpar os arquivos temporarios (objeto)
# gerados durante a compilacao, assim como os arquivos
# binarios/executaveis.
clean:
	#$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*
