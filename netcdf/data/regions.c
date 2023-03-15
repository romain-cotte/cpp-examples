#include <stdio.h>
#include <stdlib.h>
#include <netcdf.h>



void
check_err(const int stat, const int line, const char *file) {
    if (stat != NC_NOERR) {
        (void)fprintf(stderr,"line %d of %s: %s\n", line, file, nc_strerror(stat));
        fflush(stderr);
        exit(1);
    }
}

int
main() {/* create regions.nc */

    int  stat;  /* return status */
    int  ncid;  /* netCDF id */

    /* group ids */
    int regions_grp;
    int USA_grp;
    int USA_SLASH_Colorado_grp;
    int USA_SLASH_Wyoming_grp;
    int USA_SLASH_Alaska_grp;

    /* dimension ids */
    int USA_SLASH_time_dim;
    int USA_SLASH_Colorado_SLASH_stations_dim;
    int USA_SLASH_Wyoming_SLASH_stations_dim;
    int USA_SLASH_Alaska_SLASH_stations_dim;

    /* dimension lengths */
    size_t USA_SLASH_time_len = NC_UNLIMITED;
    size_t USA_SLASH_Colorado_SLASH_stations_len = 5;
    size_t USA_SLASH_Wyoming_SLASH_stations_len = 4;
    size_t USA_SLASH_Alaska_SLASH_stations_len = 3;

    /* variable ids */
    int USA_SLASH_average_temperature_id;
    int USA_SLASH_Colorado_SLASH_temperature_id;
    int USA_SLASH_Wyoming_SLASH_temperature_id;
    int USA_SLASH_Alaska_SLASH_temperature_id;

    /* rank (number of dimensions) for each variable */
#   define RANK_USA_SLASH_average_temperature 1
#   define RANK_USA_SLASH_Colorado_SLASH_temperature 2
#   define RANK_USA_SLASH_Wyoming_SLASH_temperature 2
#   define RANK_USA_SLASH_Alaska_SLASH_temperature 2

    /* variable shapes */
    int USA_SLASH_average_temperature_dims[RANK_USA_SLASH_average_temperature];
    int USA_SLASH_Colorado_SLASH_temperature_dims[RANK_USA_SLASH_Colorado_SLASH_temperature];
    int USA_SLASH_Wyoming_SLASH_temperature_dims[RANK_USA_SLASH_Wyoming_SLASH_temperature];
    int USA_SLASH_Alaska_SLASH_temperature_dims[RANK_USA_SLASH_Alaska_SLASH_temperature];

    /* enter define mode */
    stat = nc_create("regions.nc", NC_CLOBBER|NC_NETCDF4, &ncid);
    check_err(stat,__LINE__,__FILE__);
    regions_grp = ncid;
    stat = nc_def_grp(regions_grp, "USA", &USA_grp);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_grp(USA_grp, "Colorado", &USA_SLASH_Colorado_grp);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_grp(USA_grp, "Wyoming", &USA_SLASH_Wyoming_grp);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_grp(USA_grp, "Alaska", &USA_SLASH_Alaska_grp);
    check_err(stat,__LINE__,__FILE__);

    /* define dimensions */
    stat = nc_def_dim(USA_grp, "time", USA_SLASH_time_len, &USA_SLASH_time_dim);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_dim(USA_SLASH_Colorado_grp, "stations", USA_SLASH_Colorado_SLASH_stations_len, &USA_SLASH_Colorado_SLASH_stations_dim);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_dim(USA_SLASH_Wyoming_grp, "stations", USA_SLASH_Wyoming_SLASH_stations_len, &USA_SLASH_Wyoming_SLASH_stations_dim);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_dim(USA_SLASH_Alaska_grp, "stations", USA_SLASH_Alaska_SLASH_stations_len, &USA_SLASH_Alaska_SLASH_stations_dim);
    check_err(stat,__LINE__,__FILE__);

    /* define variables */

    USA_SLASH_average_temperature_dims[0] = USA_SLASH_time_dim;
    stat = nc_def_var(USA_grp, "average_temperature", NC_FLOAT, RANK_USA_SLASH_average_temperature, USA_SLASH_average_temperature_dims, &USA_SLASH_average_temperature_id);
    check_err(stat,__LINE__,__FILE__);

    USA_SLASH_Colorado_SLASH_temperature_dims[0] = USA_SLASH_time_dim;
    USA_SLASH_Colorado_SLASH_temperature_dims[1] = USA_SLASH_Colorado_SLASH_stations_dim;
    stat = nc_def_var(USA_SLASH_Colorado_grp, "temperature", NC_FLOAT, RANK_USA_SLASH_Colorado_SLASH_temperature, USA_SLASH_Colorado_SLASH_temperature_dims, &USA_SLASH_Colorado_SLASH_temperature_id);
    check_err(stat,__LINE__,__FILE__);

    USA_SLASH_Wyoming_SLASH_temperature_dims[0] = USA_SLASH_time_dim;
    USA_SLASH_Wyoming_SLASH_temperature_dims[1] = USA_SLASH_Wyoming_SLASH_stations_dim;
    stat = nc_def_var(USA_SLASH_Wyoming_grp, "temperature", NC_FLOAT, RANK_USA_SLASH_Wyoming_SLASH_temperature, USA_SLASH_Wyoming_SLASH_temperature_dims, &USA_SLASH_Wyoming_SLASH_temperature_id);
    check_err(stat,__LINE__,__FILE__);

    USA_SLASH_Alaska_SLASH_temperature_dims[0] = USA_SLASH_time_dim;
    USA_SLASH_Alaska_SLASH_temperature_dims[1] = USA_SLASH_Alaska_SLASH_stations_dim;
    stat = nc_def_var(USA_SLASH_Alaska_grp, "temperature", NC_FLOAT, RANK_USA_SLASH_Alaska_SLASH_temperature, USA_SLASH_Alaska_SLASH_temperature_dims, &USA_SLASH_Alaska_SLASH_temperature_id);
    check_err(stat,__LINE__,__FILE__);

    /* leave define mode */
    stat = nc_enddef (regions_grp);
    check_err(stat,__LINE__,__FILE__);

    /* assign variable data */

    {
    float USA_SLASH_average_temperature_data[2] = {((float)13.4167), ((float)63.416698)} ;
    size_t USA_SLASH_average_temperature_startset[1] = {0} ;
    size_t USA_SLASH_average_temperature_countset[1] = {2};
    stat = nc_put_vara(USA_grp, USA_SLASH_average_temperature_id, USA_SLASH_average_temperature_startset, USA_SLASH_average_temperature_countset, USA_SLASH_average_temperature_data);
    check_err(stat,__LINE__,__FILE__);
    }


    {
    float USA_SLASH_Colorado_SLASH_temperature_data[10] = {((float)11), ((float)12), ((float)13), ((float)14), ((float)15), ((float)61), ((float)62), ((float)63), ((float)64), ((float)65)} ;
    size_t USA_SLASH_Colorado_SLASH_temperature_startset[2] = {0, 0} ;
    size_t USA_SLASH_Colorado_SLASH_temperature_countset[2] = {2, 5};
    stat = nc_put_vara(USA_SLASH_Colorado_grp, USA_SLASH_Colorado_SLASH_temperature_id, USA_SLASH_Colorado_SLASH_temperature_startset, USA_SLASH_Colorado_SLASH_temperature_countset, USA_SLASH_Colorado_SLASH_temperature_data);
    check_err(stat,__LINE__,__FILE__);
    }


    {
    float USA_SLASH_Wyoming_SLASH_temperature_data[8] = {((float)12), ((float)13), ((float)14), ((float)15), ((float)62), ((float)63), ((float)64), ((float)65)} ;
    size_t USA_SLASH_Wyoming_SLASH_temperature_startset[2] = {0, 0} ;
    size_t USA_SLASH_Wyoming_SLASH_temperature_countset[2] = {2, 4};
    stat = nc_put_vara(USA_SLASH_Wyoming_grp, USA_SLASH_Wyoming_SLASH_temperature_id, USA_SLASH_Wyoming_SLASH_temperature_startset, USA_SLASH_Wyoming_SLASH_temperature_countset, USA_SLASH_Wyoming_SLASH_temperature_data);
    check_err(stat,__LINE__,__FILE__);
    }


    {
    float USA_SLASH_Alaska_SLASH_temperature_data[6] = {((float)13), ((float)14), ((float)15), ((float)63), ((float)64), ((float)65)} ;
    size_t USA_SLASH_Alaska_SLASH_temperature_startset[2] = {0, 0} ;
    size_t USA_SLASH_Alaska_SLASH_temperature_countset[2] = {2, 3};
    stat = nc_put_vara(USA_SLASH_Alaska_grp, USA_SLASH_Alaska_SLASH_temperature_id, USA_SLASH_Alaska_SLASH_temperature_startset, USA_SLASH_Alaska_SLASH_temperature_countset, USA_SLASH_Alaska_SLASH_temperature_data);
    check_err(stat,__LINE__,__FILE__);
    }


    stat = nc_close(regions_grp);
    check_err(stat,__LINE__,__FILE__);
    return 0;
}
