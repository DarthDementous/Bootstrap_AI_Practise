#pragma once

#include <vector>
#include <Utility.h>

#pragma region Forward Declarations
class IAgent;
#pragma endregion

enum eMessageType {
	POS_REPORT,			// Look at message content's position
	PLAYER_FOUND		// Converge on player's position
};
/**
*	@brief Singleton static class that holds messages that Agents can receive and respond to.
*/
class Blackboard {
public:
	/**
	*	@brief Clean up dynamically allocated memory held by Blackboard.
	*/
	static void Clear();

	static void Update(float a_dt);

	/**
	*	@brief Struct that defines a message to the Blackboard.
	*/
	struct Message {
		Message(eMessageType a_type, IAgent* a_content, IAgent* a_author = nullptr, double a_lifeTime = MESSAGE_LIFETIME, IAgent* a_target = nullptr) :
			type(a_type), content(a_content), author(a_author), lifeTime(a_lifeTime), target(a_target) {}

		eMessageType	type;				/*Type of message, depends how the content is processed.*/

		IAgent*			content = nullptr;	/*Data of the message.*/

		IAgent*			author = nullptr;	/*Creator of the message.*/
		IAgent*			target = nullptr;	/*Intended recipient of message, nullptr if not for a specific target.*/
		
		double			lifeTime;			/*How long to keep the message on the blackboard before removing.*/
		bool			toRemove = false;	/*Flag message for removal (marked as true when lifeTime exceeded)*/
	};

	/**
	*	@brief Add message to blackboard for all agents to see.
	*	@param a_msg is the message to add.
	*	@return void.
	*/
	static void AddMessage(Message* a_msg) { m_messages->push_back(a_msg); }

	/**
	*	@brief Find and return all un-targeted messages.
	*	@param a_vec is the vector to place the messages into.
	*	@return void.
	*/
	static void GetMessages(std::vector<Message*>& a_vec);
protected:
	static std::vector<Message*>* m_messages;		/*Static vector of held messages for agents to access.*/
private:
	/**
	*	@brief Remove all messages marked for deletion.
	*/
	static void CleanMessages();

	Blackboard();
	~Blackboard();
};