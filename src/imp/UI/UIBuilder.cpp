#include <UI/UIBuilder.h>


UIBuilder& UIBuilder::setPosition(glm::vec2 pos){
    this->pos = pos;
    return (*this);
}

UIBuilder& UIBuilder::setColor(glm::vec4 color){
    this->color = color;
    return (*this);
}

UIBuilder& UIBuilder::setSize(glm::vec2 size){
    this->size = size;
    return (*this);
}

UIBuilder& UIBuilder::setRenderType(int type){
    this->renderType = type;
    return (*this);
}

UIBuilder& UIBuilder::setTexture(std::shared_ptr<Texture> texture){
    this->texture = texture;
    return (*this);
}

UIBuilder& UIBuilder::setTexture(std::string path){
    this->texture = std::make_shared<Texture>(path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    return (*this);
}

UIBuilder& UIBuilder::setText(std::string text){
    this->text = text;
    return (*this);
}

UIBuilder& UIBuilder::setShape(Shapes shape){
    this->shape = shape;
    return (*this);
}

bool UIBuilder::checkNull(){
    
    bool result = true;

    if(texture == nullptr ) 
    {
        std::cout << "texture is null in ui builder" << std::endl;
        result = false;
    }
    if(renderType == -1) {
        std::cout << "render type has not been set in ui builder" << std::endl;
        result = false;
    }
    if(text.empty()){
        std::cout << "text is empty in ui builder" << std::endl;
        result = false;
    }

    return result;
    
}

std::shared_ptr<Button> UIBuilder::buildButton(){
    if(checkNull()){
        std::shared_ptr<Appearance2D> app = std::make_shared<Appearance2D>(
            pos,
            size,
            color,
            (*texture),
            renderType
        );

        std::shared_ptr<Button> btn = std::make_shared<Button>(scene->getVertices(), scene->currentIndex(), text, app, shape);
        return btn;
    }
    return nullptr;
}

std::shared_ptr<MenuElement> UIBuilder::buildElement(std::string type){
    if(checkNull()){
        std::shared_ptr<Appearance2D> app = std::make_shared<Appearance2D>(
            pos,
            size,
            color,
            (*texture),
            renderType
        );
        return uiFactory->create(type, scene->getVertices(), scene->currentIndex(), text, app, shape);
    }
    return nullptr;
}

std::shared_ptr<Label> UIBuilder::buildLabel(Shader textShader, std::string fontPath){

    if(checkNull()){
        std::shared_ptr<Appearance2D> app = std::make_shared<Appearance2D>(
            pos,
            size,
            color,
            (*texture),
            renderType
        );
        std::cout << "app for label created" << std::endl;

        std::shared_ptr<TextRenderer> textRenderer = std::make_shared<TextRenderer>(textShader);
        std::cout << "Text Renderer instance pointer created" << std::endl;
        std::shared_ptr<FontLoader> loader = std::make_shared<FontLoader>();
        std::cout << "Font Loader instance pointer created" << std::endl;
        textRenderer->loadCharacters(fontPath, loader);
        std::cout << "Loaded characters' font" << std::endl;

        std::shared_ptr<Label> label = std::make_shared<Label>(scene->getVertices(), scene->currentIndex(), text, app, shape, textRenderer);
        std::cout << "Label instance pointer created" << std::endl;
        return label;
    }
    return nullptr;
}
