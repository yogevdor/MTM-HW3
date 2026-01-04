#include "TaskManager.h"
#include "Person.h"
#include "SortedList.h"
#include "Task.h"

TaskManager::TaskManager() : nextId(0), size(0) {}

void TaskManager::assignTask(const string& personName, const Task& task){
  Task newTask = task;
  newTask.setId(nextId++);
  for(int i = 0; i < size; i++){
    if(employees[i].getName() == personName){
      employees[i].assignTask(newTask);
      return;
    }
  }
  if(size==MAX_PERSONS){
    throw std::runtime_error("Too many employees");
  }else{
    employees[size] = Person(personName);
    employees[size].assignTask(newTask);
    size++;
  }
}
void TaskManager::completeTask(const string& personName){
  for(int i = 0; i < size; i++){
    if(employees[i].getName() == personName){
      employees[i].completeTask();
    }
  }
}


void TaskManager::bumpPriorityByType(TaskType type, int priority){
  if(priority <=0){
    return;
  }
  for(int i = 0; i < size; i++){
    SortedList<Task> currentTasks = employees[i].getTasks();
    SortedList<Task> updatedTasks = currentTasks.apply([=](const Task& t){
      if(t.getType() == type){
        Task updatedTask(t.getPriority()+priority, type, t.getDescription());
        updatedTask.setId(t.getId());
        return updatedTask;
      }
      return t;
    });
    employees[i].setTasks(updatedTasks);
  }
}
void TaskManager::printAllEmployees() const{
  for(int i = 0; i < size; i++){
    std::cout << employees[i] << std::endl;
  }
}
void TaskManager::printAllTasks() const{
  SortedList<Task> allTasks;
  for(int i = 0; i < size; i++){
    const SortedList<Task>&tasks = employees[i].getTasks();
    for(const Task& t : tasks){
      allTasks.insert(t);
    }
  }
  for(const Task& t : allTasks){
    std::cout << t << std::endl;
  }
}
void TaskManager::printTasksByType(TaskType type) const{
  for (int i = 0; i < size; ++i) {
    const SortedList<Task>& tasks = employees[i].getTasks();
    for(const Task& t : tasks){
      if(t.getType() == type){
        std::cout << t << std::endl;
      }
    }
  }
}
