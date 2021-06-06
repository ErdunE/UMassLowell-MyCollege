package com.example.qoutelibyary.quote.videoRecord.other;


import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicAntiqueFilter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.GPUImageFilter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicBrannanFilter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicCoolFilter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicFreudFilter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicHefeFilter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicHudsonFilter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicInkwellFilter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicN1977Filter;
import com.example.qoutelibyary.quote.videoRecord.filters.gpuFilters.baseFilter.MagicNashvilleFilter;

public class MagicFilterFactory {

    private static MagicFilterType filterType = MagicFilterType.NONE;

    public static GPUImageFilter initFilters(MagicFilterType type) {
        if (type == null) {
            return null;
        }
        filterType = type;
        switch (type) {
            case ANTIQUE:
                return new MagicAntiqueFilter();
            case BRANNAN:
                return new MagicBrannanFilter();
            case FREUD:
                return new MagicFreudFilter();
            case HEFE:
                return new MagicHefeFilter();
            case HUDSON:
                return new MagicHudsonFilter();
            case INKWELL:
                return new MagicInkwellFilter();
            case N1977:
                return new MagicN1977Filter();
            case NASHVILLE:
                return new MagicNashvilleFilter();
            case COOL:
                return new MagicCoolFilter();
            case WARM:
                return new MagicWarmFilter();
            default:
                return null;
        }
    }

    public MagicFilterType getCurrentFilterType() {
        return filterType;
    }

    private static class MagicWarmFilter extends GPUImageFilter {
    }
}
