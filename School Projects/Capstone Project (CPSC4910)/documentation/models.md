# Model Code Snippets

## Linear Regression

```python
numpy.polyfit(x,y,deg,rcond=None,full=False,w=None,cov=False)
```

Fit a polynomial `p(x) = p[0] * x**deg + ... + p[deg]`

 * `x` is the array of variables , where each column is a predictor.
 * `y` is the array of variables , where each column is the actual result.
 * `deg` should be 1 for linear regression
