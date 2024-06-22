#include "ui/Appearance.h"


void from_json(const json &j, Appearance2D &appearance) {

  appearance.position.x = j.at("position").at(0).get<GLfloat>();
  appearance.position.y = j.at("position").at(1).get<GLfloat>();

  appearance.size.x = j.at("size").at(0).get<GLfloat>();
  appearance.size.y = j.at("size").at(1).get<GLfloat>();

  appearance.color.x = j.at("color").at(0).get<GLfloat>();
  appearance.color.y = j.at("color").at(1).get<GLfloat>();
  appearance.color.z = j.at("color").at(2).get<GLfloat>();
  appearance.color.w = j.at("color").at(3).get<GLfloat>();

  appearance.texturePos.x = j.at("texturePos").at(0).get<GLfloat>();
  appearance.texturePos.y = j.at("texturePos").at(1).get<GLfloat>();

  j.at("texture").get_to(appearance.texture);

  j.at("renderType").get_to(appearance.renderType);
}

void to_json(json &j, const Appearance2D &appearance)
{
  j = json{
      {"position", {appearance.position.x, appearance.position.y}},
      {"size", {appearance.size.x, appearance.size.y}},
      {"color", {appearance.color.x, appearance.color.y, appearance.color.z, appearance.color.w}},
      {"texturePos", {appearance.texturePos.x, appearance.texturePos.y}},
      {"renderType", appearance.renderType}
    };
}