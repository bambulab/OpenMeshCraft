#include "OBJReader.h"
#include "OBJWriter.h"
#include "STLReader.h"
#include "STLWriter.h"

#include "MEDITWriter.h"
#include "VTKWriter.h"

namespace OMC {

template class OBJReader<TriSoupTraits>;
template class OBJWriter<TriSoupTraits>;
template class STLReader<TriSoupTraits>;
template class STLWriter<TriSoupTraits>;

template class MEDITWriter<TetSoupTraits>;
template class VTKWriter<TetSoupTraits>;

} // namespace OMC