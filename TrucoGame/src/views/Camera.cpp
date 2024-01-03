#include "../../include/views/Camera.h"
#include "../../include/views/GraphicManager.h"

namespace TrucoGame {

    namespace Controller {

        Camera::Camera(const sf::Vector2f windowSize) :
            cameraBoundary(sf::IntRect(-1, -1, -1, -1)), windowSize(windowSize),
            camera(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f), windowSize),
            objectBoundary(sf::IntRect(-1, -1, -1, -1))
        {

        }

        Camera::~Camera() {

        }

        void Camera::setCameraBoundary(const sf::IntRect cameraBoundary) {
            this->cameraBoundary = cameraBoundary;
            adjustBoundary();
        }

        sf::View Camera::getCamera() {
            return camera;
        }

        void Camera::reset(const sf::Vector2f posCenter) {
            camera.setCenter(posCenter);
        }

        void Camera::adjustBoundary() {
            if (cameraBoundary.width != -1 && objectBoundary.width != -1) {
                if (objectBoundary.top < cameraBoundary.top) {
                    objectBoundary.top = cameraBoundary.top;
                }
                else if (objectBoundary.top + objectBoundary.height > cameraBoundary.top + cameraBoundary.height) {
                    const float dy = objectBoundary.top + objectBoundary.height - (cameraBoundary.top + cameraBoundary.height);
                    objectBoundary.top = objectBoundary.top - dy;
                }
                if (objectBoundary.left < cameraBoundary.left) {
                    objectBoundary.left = cameraBoundary.left;
                }
                else if (objectBoundary.left + objectBoundary.width > cameraBoundary.left + cameraBoundary.width) {
                    const float dx = objectBoundary.left + objectBoundary.width - (cameraBoundary.left + cameraBoundary.width);
                    objectBoundary.left = objectBoundary.left - dx;
                }
                camera.setCenter(sf::Vector2f(objectBoundary.left + objectBoundary.width / 2.0f, objectBoundary.top + objectBoundary.height / 2.0f));
            }
        }

        void Camera::setObjectBoundary(const sf::IntRect object) {
            if (object.width != -1) {
                const sf::Vector2f pos(object.left, object.top);
                const sf::Vector2f size(object.width, object.height);
                objectBoundary.width = windowSize.x / 5.0f;
                objectBoundary.height = windowSize.y / 2.8f;
                objectBoundary.left = pos.x - objectBoundary.width / 2.0f + size.x / 2.0f;
                objectBoundary.top = pos.y - objectBoundary.height / 2.0f + size.y / 2.0f;
                adjustBoundary();
            }
            else {
                this->objectBoundary = object;
            }
        }

        void Camera::update(const sf::Vector2f pos) {
            camera.setCenter(pos);
        }

        void Camera::update(const sf::Vector2f pos, sf::Vector2f size) {
            sf::Vector2f ds(0.0f, 0.0f);
            sf::Vector2f center = camera.getCenter();
            bool atualizarCamera = false;
            if (pos.x + size.x > objectBoundary.left + objectBoundary.width
                && objectBoundary.left + objectBoundary.width < cameraBoundary.left + cameraBoundary.width) {
                ds.x = (pos.x + size.x) - (objectBoundary.left + objectBoundary.width);
                center.x = pos.x + size.x - objectBoundary.width / 2.0f;
                atualizarCamera = true;
            }
            else if ((pos.x < objectBoundary.left) && (objectBoundary.left > cameraBoundary.left)) {
                ds.x = pos.x - objectBoundary.left;
                center.x = pos.x + objectBoundary.width / 2.0f;
                atualizarCamera = true;
            }
            if (pos.y + size.y > objectBoundary.top + objectBoundary.height
                && objectBoundary.top + objectBoundary.height < cameraBoundary.top + cameraBoundary.height) {
                ds.y = (pos.y + size.y) - (objectBoundary.top + objectBoundary.height);
                center.y = pos.y + size.y - objectBoundary.height / 2.0f;
                atualizarCamera = true;
            }
            else if ((pos.y < objectBoundary.top) && (objectBoundary.top > cameraBoundary.top)) {
                ds.y = pos.y - objectBoundary.top;
                center.y = pos.y + objectBoundary.height / 2.0f;
                atualizarCamera = true;
            }
            if (atualizarCamera) {
                objectBoundary.left += ds.x;
                objectBoundary.top += ds.y;
                camera.setCenter(center);
            }
        }
    }
}