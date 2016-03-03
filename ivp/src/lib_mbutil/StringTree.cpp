/*****************************************************************/
/*    NAME: Michael Benjamin and John Leonard                    */
/*    ORGN: NAVSEA Newport RI and MIT Cambridge MA               */
/*    FILE: StringTree.cpp                                       */
/*    DATE: Jan 9th 2009                                         */
/*                                                               */
/* This program is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU General Public License   */
/* as published by the Free Software Foundation; either version  */
/* 2 of the License, or (at your option) any later version.      */
/*                                                               */
/* This program is distributed in the hope that it will be       */
/* useful, but WITHOUT ANY WARRANTY; without even the implied    */
/* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR       */
/* PURPOSE. See the GNU General Public License for more details. */
/*                                                               */
/* You should have received a copy of the GNU General Public     */
/* License along with this program; if not, write to the Free    */
/* Software Foundation, Inc., 59 Temple Place - Suite 330,       */
/* Boston, MA 02111-1307, USA.                                   */
/*****************************************************************/

#include <iostream>
#include "StringTree.h"
#include "MBUtils.h"

using namespace std;

//-------------------------------------------------------------
// Procedure: addParChild

bool StringTree::addParChild(const string& parent, 
			     const string& child, 
			     bool handle_waiters)
{
  if((parent == "") || (parent == "---")) {
    StringNode new_node(child);
    m_nodes.push_back(new_node);
    return(true);
  }
  
  unsigned int i, vsize = m_nodes.size();
  for(i=0; i<vsize; i++) {
    bool added = m_nodes[i].addParChild(parent, child);
    if(added) {
      if(handle_waiters)
	handleWaiters();
      return(true);
    }
  }

  m_parents_waiting.push_back(parent);
  m_children_waiting.push_back(child);

  return(false);
}


//-------------------------------------------------------------
// Procedure: getPrintableSet

vector<string> StringTree::getPrintableSet()
{
  vector<string> rvector;
  rvector.push_back("Mode-Variable="+m_key);
  
  unsigned int i, vsize = m_nodes.size();
  for(i=0; i<vsize; i++) {
    vector<string> ivector = m_nodes[i].getPrintableSet();
    rvector = mergeVectors(rvector, ivector);
  }

  return(rvector);
}

//-------------------------------------------------------------
// Procedure: print

void StringTree::print()
{
  unsigned int i, vsize = m_nodes.size();
  for(i=0; i<vsize; i++)
    m_nodes[i].print();
}


//-------------------------------------------------------------
// Procedure: handleWaiters

void StringTree::handleWaiters()
{
  bool done = false;
  while(!done) {
    done = true;
    unsigned int i, vsize = m_parents_waiting.size();
    for(i=0; i<vsize; i++) {
      string parent = m_parents_waiting[i];
      string child  = m_children_waiting[i];
      if(parent != "") {
	bool added = addParChild(parent, child, false);
	if(added) {
	  done = false;
	  m_parents_waiting[i] = "";
	}
      }
    }
  }

}


//-------------------------------------------------------------
// Procedure: allHandled

bool StringTree::allHandled()
{
  unsigned int i, vsize = m_parents_waiting.size();
  for(i=0; i<vsize; i++) {
    if(m_parents_waiting[i] != "")
      return(false);
  }

  return(true);

}
