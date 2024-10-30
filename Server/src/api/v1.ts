import { Router } from 'express';
const router = Router();
import { SaveText } from '../controllers/database';
import axios from 'axios';
import { modelurl } from '../controllers/model';
import { saveError } from '../controllers/errors';

// localhost:8080/api/v1/

// Define your headers
const headers = {
    'Content-Type': 'application/json',
    whoami: 'senml().',
};

// Define the request configuration
const config = {
    headers: headers,
};

router.get('/modeluri', async (_req, res) => {
    res.json({ modeluri: modelurl });
});

router.get('/', async (_req, res) => {
    if (modelurl) {
        const data = await axios.get(modelurl);
        if (data.status === 200) {
            res.json({ model: 'live' });
            return;
        }
    } else {
        saveError('MLServer', 'model server down');
        res.status(500).json({ error: 'model server not up' });
        return;
    }
});

router.post('/nmc', async (req, res) => {
    const body = { nmc: req.body.data };
    try {
        const datamodel = await axios.post(`${modelurl}/nmc`, body, config);
        if (datamodel.status === 200 && datamodel.data) {
            const modeldata: SaveText = datamodel.data;
            modeldata.user = 'anonymous';
            modeldata.type = 'nmc';
            // saveText(modeldata, req.body.data);
            res.json(modeldata);
        } else {
            saveError('POST nmc', 'no data received.');
            res.status(500).json({
                error: 'Request failed or No data received',
            });
        }
    } catch (error: any) {
        saveError(error.name, error.message);
        res.status(500).json({ error: error.message });
    }
});

router.post('/logreg', async (req, res) => {
    const body = { logreg: req.body.data };
    try {
        const datamodel = await axios.post(`${modelurl}/logreg`, body, config);
        if (datamodel.status === 200 && datamodel.data) {
            const modeldata: SaveText = datamodel.data;
            modeldata.user = 'anonymous';
            modeldata.type = 'logreg';
            // saveText(modeldata, req.body.data);
            res.json(modeldata);
        } else {
            saveError('POST logreg', 'no data received.');
            res.status(500).json({
                error: 'Request failed or No data received',
            });
        }
    } catch (error: any) {
        saveError(error.name, error.message);
        res.status(500).json({ error: error.message });
    }
});

export default router;
