#include "controllers/GLSixDOFViewController.h"

namespace Sigma{
	namespace event{
		namespace handler{
			const float GLSixDOFViewController::SPEED_TRANSLATE   = 2.0f;
			const float GLSixDOFViewController::SPEED_ROTATE      = 20.0f * 3.14159f;
			const float GLSixDOFViewController::BOOST_MULTIPLIER  = 2.0f;

			GLSixDOFViewController::GLSixDOFViewController(IGLView* view, PhysicsController* mover) : mover(mover) {
				this->keys.push_back('W');
				this->keys.push_back('A');
				this->keys.push_back('S');
				this->keys.push_back('D');
				this->keys.push_back('B');
				this->keys.push_back('Q');
				this->keys.push_back('Z');
				this->keys.push_back('R');
				this->keys.push_back('T');
				this->keys.push_back('E');
				this->keys.push_back('C');
				this->keys.push_back('F');
				this->keys.push_back('G');
			}

			void GLSixDOFViewController::KeyStateChange(const unsigned int key, const KEY_STATE state) {
				// Store the new key state
				this->keyState[key] = state;

				float speed = this->keyState['B'] == KS_DOWN ? SPEED_TRANSLATE * BOOST_MULTIPLIER : SPEED_TRANSLATE;

				// Translation keys
				float fwd = 0.0f, strafe = 0.0f, rise = 0.0f;
				if (this->keyState['W'] == KS_DOWN) { // Move forward
					fwd += speed;
				}
				if (this->keyState['S'] == KS_DOWN) { // Move backward
					fwd -= speed;
				}
				if (this->keyState['F'] == KS_DOWN) { // Strafe left
					strafe -= speed;
				}
				if (this->keyState['G'] == KS_DOWN) { // Strafe right
					strafe += speed;
				}
				if (this->keyState['E'] == KS_DOWN) { // Move up
					rise += speed;
				}
				if (this->keyState['C'] == KS_DOWN) { // Move down
					rise -= speed;
				}

				// remove previous force and add new one
				this->mover->RemoveForce(this->_translate);
				this->_translate = glm::vec3(strafe, rise, fwd);
				this->mover->AddForce(this->_translate);

				// Rotation Keys
				float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;
				if (this->keyState['A'] == KS_DOWN) { // pan (yaw) left
					yaw -= SPEED_ROTATE;
				}
				if (this->keyState['D'] == KS_DOWN) { // pan (yaw) right
					yaw += SPEED_ROTATE;
				}
				if (this->keyState['Q'] == KS_DOWN) { // pitch Up
					pitch -= SPEED_ROTATE;
				}
				if (this->keyState['Z'] == KS_DOWN) { // pitch Down
					pitch += SPEED_ROTATE;
				}
				if (this->keyState['R'] == KS_DOWN) { // roll left
					roll -= SPEED_ROTATE;
				}
				if (this->keyState['T'] == KS_DOWN) { // roll right
					roll += SPEED_ROTATE;
				}

				// remove previous force and add new one
				this->mover->RemoveRotationForce(this->_rotate);
				this->_rotate = glm::vec3(pitch, yaw, roll);
				this->mover->AddRotationForce(this->_rotate);

			} // function KeyStateChange
		}
	}
} // namespace Sigma::event::handler
