//#include "Ai._Base.h"
//#include "Ai_Organism.h"
//#include "SharedContext.h"
//#include "Engine.h"
//
//static const std::string S_TASK_IDLE{ "Idle" };
//static const std::string S_TASK_WAITING{ "Waiting" };
//
//////////////////////////////////////////////////////////////
//Ai_Base::Ai_Base() : m_currentTask{ &S_TASK_IDLE }, m_isDone{ true }, m_waitCoundown{ 0 }, m_taskMap{}, m_taskQueue{} {
//	registerTask<Ai_Base>(S_TASK_WAITING, &Ai_Base::Task_Waiting);
//	registerTask<Ai_Base>(S_TASK_IDLE, &Ai_Base::Task_Idle);
//}
//
//////////////////////////////////////////////////////////////
//bool Ai_Base::executeTask(const std::string& t_taskName, Actor_Base* t_owner, const float& t_elapsed) {
//	auto it{ m_taskMap.find(t_taskName) };
//	if (it == m_taskMap.end()) { return false; }
//	it->second(t_owner, t_elapsed);
//	return true;
//}
//
//////////////////////////////////////////////////////////////
//void Ai_Base::pollTasks() {
//
//
//	if (m_waitCoundown < 0) {
//		m_waitCoundown = 0.f;
//	}
//	else if (m_waitCoundown > 0) {
//		m_currentTask = &S_TASK_WAITING;
//		return;
//	}
//
//	// Current task is at front always
//	if (m_taskQueue.empty()) {
//		m_currentTask = &S_TASK_IDLE;
//		return;
//	}
//	else if (m_isDone) {
//		m_taskQueue.pop();
//	}
//	m_currentTask = &m_taskQueue.front();
//
//}
//
//////////////////////////////////////////////////////////////
//const float& Ai_Base::getWaitCountDown()const { return m_waitCoundown; }
//
//////////////////////////////////////////////////////////////
//void Ai_Base::setWaitCountDown(const float& t_seconds) { m_waitCoundown = t_seconds; }
//
//////////////////////////////////////////////////////////////
//const std::string& Ai_Base::getCurrentTask()const { return *m_currentTask; }
//
//////////////////////////////////////////////////////////////
//bool Ai_Base::hasTask(const std::string& t_taskName)const { return (m_taskMap.find(t_taskName) != m_taskMap.cend()); }
//
//////////////////////////////////////////////////////////////
//bool Ai_Base::getIsDone()const { return m_isDone; }
//
//
//////////////////////////////////////////////////////////////
//void Ai_Base::update(Actor_Base* t_owner, const float& t_elapsed) {
//	pollTasks();
//	executeTask(*m_currentTask, t_owner, t_elapsed);
//}
//
//////////////////////////////////////////////////////////////
//void Ai_Base::Task_Idle(Actor_Base* t_owner, const float& t_elapsed) {}
//
//////////////////////////////////////////////////////////////
//void Ai_Base::Task_Waiting(Actor_Base* t_owner, const float& t_elapsed) {
//	m_waitCoundown -= t_owner->getContext().m_engine->getElapsed().asSeconds();
//}