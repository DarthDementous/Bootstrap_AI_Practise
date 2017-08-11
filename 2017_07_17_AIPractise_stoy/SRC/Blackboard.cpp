#include "Blackboard.h"

// Initialize static variables
std::vector<Blackboard::Message*>* Blackboard::m_messages = new std::vector<Blackboard::Message*>;

void Blackboard::CleanMessages()
{
	for (auto iter = m_messages->begin(); iter != m_messages->end(); iter++) {
		if ((*iter)->toRemove) {
			// Clear allocated memory
			delete (*iter);

			// Remove from vector
			iter = m_messages->erase(iter);
		}
	}
}

void Blackboard::Clear()
{
	for (auto msg : *m_messages) {
		delete msg;
	}

	m_messages->clear();
	delete m_messages;
}

void Blackboard::Update(float a_dt)
{
	// Decay messages and mark for deletion
	for (auto msg : *m_messages) {
		msg->lifeTime -= a_dt;

		// Message expired, flag for removal
		if (msg->lifeTime < 0.0) {
			msg->toRemove = true;
		}
	}

	CleanMessages();
}

void Blackboard::GetMessages(std::vector<Message*>& a_vec)
{
	for (auto msg : *m_messages) {
		a_vec.push_back(msg);
	}
}
