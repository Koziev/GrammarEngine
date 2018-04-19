#include <lem/solarix/SynPattern.h>
#include <lem/solarix/PatternOptionalPoints.h>

using namespace Solarix;


PatternOptionalPoints::PatternOptionalPoints(const PatternOptionalPoints & x)
{
    for (auto p : x.points)
    {
        points.push_back(new SynPatternPoint(*p));
    }
}


void PatternOptionalPoints::operator=(const PatternOptionalPoints & x)
{
    for (auto point : points)
    {
        delete point;
    }
    points.clear();

    for (auto point : x.points)
    {
        points.push_back(new SynPatternPoint(*point));
    }

    return;
}



PatternOptionalPoints::~PatternOptionalPoints()
{
    for (auto point : points)
    {
        delete point;
    }
}


bool PatternOptionalPoints::operator!=(const PatternOptionalPoints & x) const
{
    if (points.size() != x.points.size())
        return false;

    for (lem::Container::size_type i = 0; i < points.size(); ++i)
    {
        if (!points[i]->Equal(*x.points[i]))
            return false;
    }

    return true;
}


void PatternOptionalPoints::SaveBin(lem::Stream & bin) const
{
#if defined SOL_SAVEBIN
    bin.write_int(points.size());
    for (auto point : points)
    {
        point->SaveBin(bin);
    }
#endif
    return;
}


void PatternOptionalPoints::LoadBin(lem::Stream & bin)
{
    int n = bin.read_int();
    for (int i = 0; i < n; ++i)
    {
        SynPatternPoint * p = new SynPatternPoint();
        p->LoadBin(bin);
        points.push_back(p);
    }

    return;
}
