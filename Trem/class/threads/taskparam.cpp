/*
Implementa tarefa para programas multitheads
Copyright (C) 2013  Rafael Alceste Berri rafaelberri@gmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

//#include "stdafx.h"
#include "taskparam.h"
//#include "stdio.h"
//#include <iostream>

#ifdef __unix__
#include <pthread.h>
#include <unistd.h>
#include <cxxabi.h>
//#include <thread>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#ifdef __unix__
void *execParam(void *ptr)
{
  try
  {
    //printf("ExecParam ini %li\n", ThreadParam::ID());
    ThreadParamNode *node = (ThreadParamNode *) ptr;
    //printf("ExecParam Exec -1 %li\n", ThreadParam::ID());
    while(1)
    {
      void *job = NULL;
      
      //printf("ExecParam 0 Exec %li\n", ThreadParam::ID());
      if(node->jobs == NULL)
      {
        ThreadParam::SleepMS(50);
        continue;
      }
      
      //printf("ExecParam Exec 1 %li\n", ThreadParam::ID());
      
      node->semaJobs->Lock();
      if(node->jobs->size() > 0)
      {
        //printf("ExecParam Exec 1.1 new job %i %li\n", node->jobs->size(), ThreadParam::ID());
        //int uuu;
        //cin >> uuu;
        job = *(node->jobs->begin());
        node->jobs->erase(node->jobs->begin());
      }
      node->semaJobs->Unlock();
      
      //printf("ExecParam Exec 2 %li\n", ThreadParam::ID());
      if(job == NULL)
      {
        node->thread->ConcludeProcess();
        ThreadParam::SleepMS(50);
        //printf("ExecParam Exec 2.1 %li\n", ThreadParam::ID());
        continue;
      }
      
      //vector<void *> jobs;
      //sema semaJobs;
      
      //printf("ExecParam 3 Exec %li\n", Thread::ID());
      //int kkk;
      //cin >> kkk;
      
      node->thread->RestartProcess();
      node->task->Exec(node->thread, job);
      //((Task *)ptr)->Exec();
    }
    //printf("ExecParam depois %li\n", Thread::ID());
  }   
  catch (abi::__forced_unwind&)
  {  // handle pthread_cancel stack unwinding exception
      throw;
  }
  catch (exception &ex) 
  {
      throw ex;
  }
  
	return NULL;
}
#elif defined(_WIN32) || defined(WIN32)
DWORD WINAPI execParam(LPVOID ptr)
{
  ThreadParamNode *node = (ThreadParamNode *) ptr;
  node->task->Exec(node->thread, node->data);
  
  delete node;
	//((Task *)ptr)->Exec();
	return 0;
}
#endif

ThreadParam::ThreadParam(TaskParam* eTask)
{
  //printf("Criando a thread INI ...\n");
  node = new ThreadParamNode();
  node->thread = this;
  node->task = eTask;
  node->jobs = &jobs;
  node->semaJobs = &semaJobs;
  
#ifdef __unix__
	int ret;
	//printf("Criando thread thread %li \n", this->id);
  ret = pthread_create(&this->id, NULL, execParam, (void*)node);
  //printf("Criada thread %li  ret %i \n", this->id, ret);
#elif defined(_WIN32) || defined(WIN32)
	this->id = CreateThread(0, 0, execParam, (void*)node, 0, NULL);
#endif
  //printf("Criando a thread FIM ...\n");
}

ThreadParam::~ThreadParam()
{
  //printf("Stop INI th %li\n", ID());
  if (this->id != 0)
  {
#ifdef __unix__
    //pthread_cancel(this->id);
    void *res;
    //int s;

    pthread_cancel(id);
    pthread_join(id, &res);
    //cout << "Thread cancelada " << this->id << endl;
#elif defined(_WIN32) || defined(WIN32)
		CloseHandle(id);
#endif
  }
	delete node;
  //printf("Stop FIM th %li\n", ID());
}

void ThreadParam::RestartProcess()
{
  semaConcluded.Lock();
  concluded = false;
  semaConcluded.Unlock();
}

void ThreadParam::ConcludeProcess()
{
  //printf("ConcludeProcess INI th %li\n", ID());
  semaConcluded.Lock();
  concluded = true;
  semaConcluded.Unlock();
  //printf("ConcludeProcess FIM th %li\n", ID());
  
  //while(1)
  //  Thread::SleepMS(50); // Waiting for kill (the thread)
}

bool ThreadParam::Concluded()
{
  bool ret;
  //printf("Concluded INI th %li\n", ID());
  semaConcluded.Lock();
  ret = concluded;
  semaConcluded.Unlock();
  //printf("Concluded FIM th %li\n", ID());
  
  return ret;
}

bool ThreadParam::NewJob(void* data)
{
  semaJobs.Lock();
  jobs.push_back(data);
  semaJobs.Unlock();
  
  //printf("NewJob!!! %i %li", jobs.size(), id);
  //int kkk;
  //cin >> kkk;
  
  node->thread->RestartProcess();
  
  //printf("NewJobFim !!! %li fim", id);
  
  return true;
}

unsigned int ThreadParam::QtdJobs()
{
  unsigned int qtd = 0;
  semaJobs.Lock();
  qtd = jobs.size();
  semaJobs.Unlock();
  
  return qtd;
}

long ThreadParam::GetID()
{
#ifdef __unix__
	return id;
#elif defined(_WIN32) || defined(WIN32)
	return (long int) id();
#endif
}

bool ThreadParam::IsCurrentThread()
{
  if((long int) this->id == ThreadParam::ID())
    return true;
  return false;
}



// static

long int ThreadParam::ID()
{
#ifdef __unix__
	// implementar para linux
	return pthread_self();
#elif defined(_WIN32) || defined(WIN32)
	return (long int) GetCurrentThreadId();
#endif
}

void ThreadParam::SleepMS(unsigned int tempo)
{
#ifdef __unix__
	usleep(tempo * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#elif defined(_WIN32) || defined(WIN32)
	Sleep(tempo);
#endif
}




TaskParam::TaskParam()
{
}

TaskParam::~TaskParam()
{
}

bool TaskParam::Exec(ThreadParam* thread, void* data)
{
  //delete (ThreadParam *) data;
  
  return true;
}


/*
Task::Task()
{
	status = TaskStatusNotSubmitted;
	threads = 0;
}

Task::~Task()
{
}

void Task::StatusSet(TaskStatus_t status)
{
	statusSema.Lock();
	this->status = status;
	statusSema.Unlock();
}

TaskStatus_t Task::Status()
{
	TaskStatus_t state;

	statusSema.Lock();
	state = status;
	statusSema.Unlock();
	return state;
}

void Task::ThreadAdd()
{
	semaThreads.Lock();
	threads++;
	semaThreads.Unlock();
}

bool Task::ThreadRemove()
{
	bool retorno;
	
	semaThreads.Lock();
	if (threads > 0)
	{
		threads--;
		retorno = true;
	}
	else
		retorno = false;
	
	if (threads == 0)
		this->StatusSet(TaskStatusCompleted);
	semaThreads.Unlock();

	return retorno;
}

unsigned int Task::ThreadsQtdExec()
{
	unsigned int tam;
	
	semaThreads.Lock();
	tam = threads;
	semaThreads.Unlock();

	return tam;
}


bool Task::Exec()
{
	return false;
}
*/
