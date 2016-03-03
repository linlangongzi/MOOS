/*****************************************************************/
/*    NAME: Michael Benjamin and John Leonard                    */
/*    ORGN: NAVSEA Newport RI and MIT Cambridge MA               */
/*    FILE: VPlug_Markers.h                                      */
/*    DATE: July 5th, 2008                                       */
/*****************************************************************/

#ifndef VMARKER_SET_HEADER
#define VMARKER_SET_HEADER

#include <vector>
#include <string>
#include "ColorPack.h"

class CMOOSGeodesy;
class VPlug_Markers {
public:
  VPlug_Markers();
  virtual ~VPlug_Markers() {};

  bool addVMarker(const std::string& description, 
		  CMOOSGeodesy& geodesy);

  bool setParam(const std::string& param, std::string value);
  
  unsigned int size()          {return(m_marker_type.size());};
  double   getMarkerGScale()   {return(m_marker_scale_global);}
  bool     viewable(const std::string& s="all");

  std::string getMarkerType(int ix);
  double      getMarkerXPos(int ix);
  double      getMarkerYPos(int ix);
  double      getMarkerWidth(int ix);
  std::string getMarkerLabel(int ix);

  int            getMarkerColorCount(int ix);
  std::string    getMarkerColorString(int mix, int cix);
  std::vector<ColorPack> getMarkerColorVectors(int mix);

  ColorPack getLabelColor() {return(m_label_color);};

  std::vector<std::string> getParamReport() const;

protected:
  void addVMarker(std::string mtype, double xpos, double ypos,
		  double mscale, std::string label, std::string colors);
  

protected:
  std::vector<std::string>  m_marker_type;
  std::vector<double>       m_marker_xpos;
  std::vector<double>       m_marker_ypos;
  std::vector<double>       m_marker_width;
  std::vector<std::string>  m_marker_label;

  ColorPack  m_label_color_default;
  ColorPack  m_label_color;
  int        m_label_color_index;

  std::vector<std::vector<std::string> > m_marker_colors;
  std::vector<std::vector<ColorPack> >   m_marker_cpacks;
  

  double m_marker_scale_global;
  bool   m_markers_viewable;
  bool   m_marker_labels_viewable;
};

#endif