from netCDF4 import Dataset
import xarray as xr

ds = xr.open_dataset("data/regions.nc")

file = 'data/regions.nc'
with Dataset(file) as f:
    g = f.groups['USA']
    print(f"g = {g}")


# ##################
# # DISPLAY VALUES #
# ##################
# arr: np.ndarray = ds.loc[dict(lon=-179.5, lat=-89.5, time=datetime(2022, 1, 1))]["variable"].values
# print(arr)
# r = ds.sel(latitude=40, longitude=10)
# for x in r:
#     print("{}: {}".format(x, r[x].values))
