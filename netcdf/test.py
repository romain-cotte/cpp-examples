import pandas as pd

df = pd.DataFrame(data={
  "id": [0, 1],
  "col1": [1, 2],
  "col2": ["a", "b"],
})


def test(x):
    print(f"x = {x}")
    return 0

print(":", [k for k in map(test, df["col1"])])


# print(f"a = {0}")


# from netCDF4 import Dataset
# import xarray as xr

# ds = xr.open_dataset("data/regions.nc")

# file = 'data/regions.nc'
# with Dataset(file) as f:
#     g = f.groups['USA']
#     print(f"g = {g}")


# ##################
# # DISPLAY VALUES #
# ##################
# arr: np.ndarray = ds.loc[dict(lon=-179.5, lat=-89.5, time=datetime(2022, 1, 1))]["variable"].values
# print(arr)
# r = ds.sel(latitude=40, longitude=10)
# for x in r:
#     print("{}: {}".format(x, r[x].values))
